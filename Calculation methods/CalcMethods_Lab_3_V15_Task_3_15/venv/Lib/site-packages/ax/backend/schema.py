"""Ax GraphQL schema
1. Combines all mutations, queryes and subscribtions from schemas folder.
    Creates static part of schema from them.
2. Creates dynamic part of schema. For each AxGrid the dynamic schema is created
    Schema contains all fields of form. Rows are filtered using AxGris server
    filter. The name of schema is FormName+GridName. If grid is default, the
    additional schema is created, named FormName.
"""
import sys
import json
import graphene
from loguru import logger
from sqlalchemy import literal
from graphene_sqlalchemy import SQLAlchemyConnectionField
from dotmap import DotMap

from backend.schemas.users_schema import UsersQuery
from backend.schemas.users_schema import UsersMutations, UsersSubscription
from backend.schemas.home_schema import HomeQuery, HomeMutations
from backend.schemas.form_schema import FormQuery, FormMutations
from backend.schemas.workflow_schema import WorkflowMutations, WorkflowQuery
from backend.schemas.action_schema import ActionQuery, ActionMutations, \
    ActionSubscription
from backend.schemas.grids_schema import GridsQuery, GridsMutations
from backend.schemas.pages_schema import PagesQuery, PagesMutations
from backend.schemas.marketplace_schema import MarketplaceQuery,\
    MarketplaceMutations
from backend.schemas.fields_schema import FieldsQuery, FieldsMutations,\
    FieldsSubscription
from backend.schemas.types import Form, FieldType, Field, Grid, \
    Column, User, Role, State, Action, RoleFieldPermission, Group2Users, \
    Action2Role, State2Role, Role2Users, PositionInput, Page, Page2Users

from backend.model import AxForm
import backend.model as ax_model
import backend.dialects as ax_dialects
import backend.auth as ax_auth
import backend.exec as ax_exec


this = sys.modules[__name__]
schema = None

#  Dict used to determin what graphene type to use for AxFieldType.value_type
type_dictionary = {
    'text': graphene.String,
    'TEXT': graphene.String,
    'VARCHAR(255)': graphene.String,
    'INT': graphene.Int,
    'DECIMAL(65,2)': graphene.Float,
    'BOOL': graphene.Boolean,
    'GUID': graphene.String,
    'JSON': graphene.String,
    'TIMESTAMP': graphene.Int,
    'BLOB': graphene.String
}

# Static GQL types. Are same as SqlAlchemy model.
gql_types = [
    Form,
    FieldType,
    Field,
    Grid,
    Column,
    User,
    Role,
    State,
    Action,
    RoleFieldPermission,
    Group2Users,
    Action2Role,
    State2Role,
    Role2Users,
    Page,
    Page2Users,
    PositionInput
]

# Dynamic GQL types.
type_classes = {}


class Query(HomeQuery, FormQuery, UsersQuery, GridsQuery, WorkflowQuery,
            ActionQuery, PagesQuery, MarketplaceQuery, FieldsQuery,
            graphene.ObjectType):
    """Combines all schemas queryes"""
    # TODO - check if this fields are needed? Maybe custom queryes are enough?
    forms = SQLAlchemyConnectionField(Form)
    field_types = SQLAlchemyConnectionField(FieldType)
    fields = SQLAlchemyConnectionField(Field)
    grids = SQLAlchemyConnectionField(Grid)
    columns = SQLAlchemyConnectionField(Column)
    users = SQLAlchemyConnectionField(User)
    roles = SQLAlchemyConnectionField(Role)
    states = SQLAlchemyConnectionField(State)
    actions = SQLAlchemyConnectionField(Action)
    role_field_permissions = SQLAlchemyConnectionField(RoleFieldPermission)
    group_to_users = SQLAlchemyConnectionField(Group2Users)


class Mutations(HomeMutations, FormMutations, UsersMutations, GridsMutations,
                WorkflowMutations, PagesMutations, ActionMutations,
                MarketplaceMutations, FieldsMutations, graphene.ObjectType):
    """Combines all schemas mutations"""


class Subscription(UsersSubscription, ActionSubscription, FieldsSubscription,
                   graphene.ObjectType):
    """Combines all schemas subscription"""


async def exec_grid_code(form, grid, arguments=None, current_user=None):
    """ Execute python code to get SQL query for specific grid """

    db_fields_sql = ", ".join(
        '"' + field.db_name + '"' for field in form.db_fields)

    if db_fields_sql:
        db_fields_sql = ", " + db_fields_sql

    fields_sql = (f'"guid", "axState" {db_fields_sql}')

    localz = dict()
    ax = DotMap()  # javascript style dicts item['guid'] == item.guid
    ax.db_fields = fields_sql
    ax.db_table = form.db_name
    ax.row.guid = form.row_guid
    ax.arguments = arguments
    ax.user_email = None
    ax.user_guid = None
    if current_user:
        ax.user_email = current_user.get("email", None)
        ax.user_guid = current_user.get("user_id", None)
    ax.form = form
    ax.grid = grid
    ax.sql = ax_dialects.dialect.custom_query

    localz['ax'] = ax

    try:
        # exec(str(grid.code), globals(), localz)   # pylint: disable=exec-used
        await ax_exec.aexec(code=str(grid.code), localz=localz, ax=ax)
        ret_ax = localz['ax']
        ret_query = None
        if ret_ax and ret_ax.query:
            ret_query = str(ret_ax.query)
        return ret_query
    except SyntaxError as err:
        logger.exception(
            f'Error in query for [grid.name] - SyntaxError - {err}')
        return None
    except Exception as err:    # pylint: disable=broad-except
        logger.exception(
            f'Error in query for [grid.name] - SyntaxError - {err}')
        return None


def make_query_resolver(db_name, type_class):
    """ Dynamicly create resolver for GrapQL query based on
        db_name - db_name of AxForm + db_name of AxGrid.
        or only db_name of AxForm for default view grid

        Example:
        db_name=MyUberFormGridOne
        MyUberForm is form name
        GridOne is grid name

    """

    async def resolver(
            self, info, arguments=None, update_time=None, quicksearch=None,
            guids=None):
        del update_time, self
        err = f"Schema -> Resolver for {db_name}"
        with ax_model.try_catch(info.context['session'], err) as db_session:
            current_user = info.context['user']
            # Find AxForm with name that db_name is started with
            ax_form = None
            found_forms = db_session.query(AxForm).filter(
                literal(db_name).startswith(AxForm.db_name)
            ).all()

            ax_grid = {}
            default_grid = {}

            for form in found_forms:
                # iterate all grids to know, what grid to use
                for grid in form.grids:
                    if form.db_name + grid.db_name == db_name:
                        ax_grid = grid
                        ax_form = form
                    if grid.is_default_view and form.db_name == db_name:
                        default_grid = grid
                        ax_form = form

            grid_to_use = ax_grid or default_grid
            if not grid_to_use:
                return None

            # TODO Add paging

            results = None

            if quicksearch or guids:
                # Quicksearch or 1tom query
                # TODO check if permissions needed !IMPORTANT
                results = await ax_dialects.dialect.select_all(
                    db_session=db_session,
                    ax_form=ax_form,
                    quicksearch=quicksearch,
                    guids=guids)
            else:
                # Normal gql query
                arguments_dict = None
                if arguments:
                    try:
                        arguments_dict = json.loads(arguments)
                    except Exception as err:
                        logger.exception(
                            f'Error reading arguments for grid query - {err}')
                        raise

                sql = None
                if grid_to_use.code:
                    sql = await exec_grid_code(
                        form=ax_form,
                        grid=grid_to_use,
                        arguments=arguments_dict,
                        current_user=current_user)
                else:
                    sql = ax_dialects.default_grid_query

                results = await ax_dialects.dialect.select_custom_query(
                    db_session=db_session,
                    ax_form=ax_form,
                    sql=sql,
                    arguments=arguments_dict)

            if not results:
                return None

            current_user = info.context['user']
            user_guid = None
            if current_user:
                user_guid = current_user["user_id"]

            allowed_fields = await ax_auth.get_grid_allowed_fields_dict(
                ax_form=ax_form,
                user_guid=user_guid)

            result_items = []
            for row in results:
                kwargs = {}
                row_state_name = row["axState"]
                for key, value in row.items():
                    if current_user and current_user['is_admin']:
                        kwargs[key] = await ax_dialects.dialect.conver_for_graphql(value)
                    elif (key in allowed_fields[row_state_name] and
                          allowed_fields[row_state_name][key] and
                          allowed_fields[row_state_name][key] > 0):
                        kwargs[key] = await ax_dialects.dialect.conver_for_graphql(value)
                    elif key == 'guid':
                        kwargs[key] = value
                    else:
                        kwargs[key] = None

                result_items.append(type_class(**kwargs))

            return result_items

    resolver.__name__ = f'resolve_{db_name}'
    return resolver


def make_to1_resolver(ax_field_guid, to1_field_db_name, related_form_db_name,
                      class_name):
    """ Creates resolver for to1 field. It gets value of field (guid)
        then makes sql query and returns right graphene field as query result"""

    async def resolver(parent, info):
        err = f"Error in {class_name} -> {ax_field_guid} resolver"
        with ax_model.try_catch(info.context['session'], err) as db_session:

            kwargs = {}
            field_value = getattr(parent, to1_field_db_name)
            if field_value:
                ax_form = db_session.query(AxForm).filter(
                    AxForm.db_name == related_form_db_name
                ).first()

                results = await ax_dialects.dialect.select_one(
                    db_session=db_session,
                    form=ax_form,
                    fields_list=ax_form.db_fields,
                    row_guid=field_value)

                if results:
                    for key, value in results[0].items():
                        kwargs[key] = await ax_dialects.dialect.conver_for_graphql(value)

                if class_name in type_classes:
                    return type_classes[class_name](**kwargs)
            return None

    resolver.__name__ = f'resolve_{to1_field_db_name}'
    return resolver


def make_tom_resolver(ax_field_guid, to1_field_db_name, related_form_db_name,
                      class_name):
    """ Creates resolver for tom field. It gets value of field
        (json with list of guids). then makes sql query and returns graphene
        List as query result"""

    async def resolver(parent, info):
        err = f"Error in {class_name} -> {ax_field_guid} resolver"
        with ax_model.try_catch(info.context['session'], err) as db_session:

            ret_result = []

            field_value = getattr(parent, to1_field_db_name)
            if field_value:
                guids_list = json.loads(field_value)
                ax_form = db_session.query(AxForm).filter(
                    AxForm.db_name == related_form_db_name
                ).first()

                items = {
                    "items": guids_list
                }

                results = await ax_dialects.dialect.select_all(
                    db_session=db_session,
                    ax_form=ax_form,
                    quicksearch=None,
                    guids=json.dumps(items))

                if results:
                    for row in results:
                        kwargs = {}
                        for key, value in row.items():
                            kwargs[key] = await ax_dialects.dialect.conver_for_graphql(value)
                        if class_name in type_classes:
                            row_class = type_classes[class_name](**kwargs)
                            ret_result.append(row_class)

            return ret_result

    resolver.__name__ = f'resolve_{to1_field_db_name}'
    return resolver


def get_class_name(form_db_name, grid_db_name):
    """ makes form db_name uppercase + grid db_name """
    capital_form_db_name = form_db_name[0].upper() + form_db_name[1:]
    class_name = capital_form_db_name + grid_db_name
    return class_name


def create_class_fields(form):
    """ Creates graphene fields for each AxField of form.
        If field is to1 or tom - creates resolver for that field
     """
    class_fields = {}
    class_fields['guid'] = graphene.String()
    class_fields['axState'] = graphene.String()
    class_fields['axLabel'] = graphene.String()

    # Add fields for each field of AxForm
    for field in form.db_fields:
        if (field.is_relation_field and field.options and
                field.options['form'] and field.options['grid']):

            form_db_name = field.options['form']
            grid_db_name = field.options['grid']
            class_name = get_class_name(form_db_name, grid_db_name)

            # if class_name in type_classes:
            
            # This is same as -> field_class = lambda: type_classes[class_name]
            # def field_class():
            #     return type_classes[class_name]
            field_class = lambda: type_classes[class_name]

            if field.is_to1_field:
                resolver = make_to1_resolver(
                    ax_field_guid=field.guid,
                    class_name=class_name,
                    related_form_db_name=form_db_name,
                    to1_field_db_name=field.db_name)

                class_fields[field.db_name] = graphene.Field(field_class)
                class_fields[f'resolve_{field.db_name}'] = resolver
            elif field.is_tom_field:
                resolver = make_tom_resolver(
                    ax_field_guid=field.guid,
                    class_name=class_name,
                    related_form_db_name=form_db_name,
                    to1_field_db_name=field.db_name)

                class_fields[field.db_name] = graphene.List(field_class)
                class_fields[f'resolve_{field.db_name}'] = resolver
        else:
            field_type = (
                type_dictionary[field.field_type.value_type])
            class_fields[field.db_name] = field_type()

    return class_fields





def init_schema(db_session):
    """Initiate GQL schema. Create dynamic part of schema and combine it with
    static part take from schemas folder"""
    error_msg = "Schema -> init_schema. Error initiating GraphQL shcema."
    with ax_model.try_catch(db_session, error_msg) as db_session:
        # Create typeClass based on each AxForm
        this.schema = None
        all_types = gql_types.copy()  # Add dynamic types to GQL schema

        ax_forms = db_session.query(AxForm).all()
        for form in ax_forms:
            for grid in form.grids:
                # For each grid we create Graphene field with name FormGrid
                capital_form_db_name = form.db_name[0].upper(
                ) + form.db_name[1:]
                class_name = capital_form_db_name + grid.db_name

                class_fields = create_class_fields(form)

                if class_fields:
                    # Create graphene class and append class dict
                    graph_class = type(
                        class_name,
                        (graphene.ObjectType,),
                        class_fields,
                        name=class_name,
                        description=form.name
                    )
                    type_classes[class_name] = graph_class

                    # if grid is default view we add enother class with name
                    # Form without Grid name
                    if grid.is_default_view is True:
                        default_class_name = form.db_name[0].upper(
                        ) + form.db_name[1:]

                        default_graph_class = type(
                            default_class_name,
                            (graphene.ObjectType,),
                            class_fields,
                            name=default_class_name,
                            description=form.name
                        )
                        type_classes[default_class_name] = default_graph_class


        # Dynamicly crate resolvers for each typeClass
        # Iterate throw created classes and create resolver for each
        dynamic_fields = {}
        for key, type_class in type_classes.items():
            all_types.append(type_class)
            dynamic_fields[key] = graphene.List(
                type_class,
                update_time=graphene.Argument(
                    type=graphene.String, required=False),
                quicksearch=graphene.Argument(
                    type=graphene.String, required=False),
                guids=graphene.Argument(
                    type=graphene.String, required=False),
                arguments=graphene.Argument(
                    type=graphene.String, required=False)
            )

            dynamic_fields['resolve_%s' % key] = make_query_resolver(
                key, type_class)

        # Combine static schema query and dynamic query
        DynamicQuery = type('DynamicQuery', (Query,), dynamic_fields)

        this.schema = graphene.Schema(
            query=DynamicQuery,
            mutation=Mutations,
            types=all_types,
            subscription=Subscription
        )


def init_schema_standalone():
    """ Initiate GQL schema without db_session """
    error_msg = "Schema -> init_schema. Error initiating GraphQL shcema."
    with ax_model.scoped_session(error_msg) as db_session:
        init_schema(db_session)
