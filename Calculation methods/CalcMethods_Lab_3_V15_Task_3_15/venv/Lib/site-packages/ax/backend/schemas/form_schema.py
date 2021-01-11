"""This is part of GraphQL schema (Mutaions, Queryes, Subscriptions).
Defines manipulation with form AxForm.
All mutations are used in form constructor - create/update/delete for Tab, Field
Query form_data is used in AxForm.vue as main form query.
"""
# import os
import uuid
import json
import graphene
# from loguru import logger
# from sqlalchemy.exc import DatabaseError

from backend.model import AxForm, AxField, AxFieldType, \
    AxRoleFieldPermission, AxColumn
import backend.model as ax_model
import backend.misc as ax_misc
import backend.dialects as ax_dialects
# import backend.cache as ax_cache
import backend.auth as ax_auth
from backend.auth import ax_admin_only

from backend.schemas.types import Form, Field, PositionInput, Role
import backend.schemas.action_schema as action_schema
import backend.fields.AxHtmlGenerated as AxFieldAxHtmlGenerated  # pylint: disable=unused-import
import backend.fields.AxAuthor as AxFieldAxAuthor  # pylint: disable=unused-import


async def exec_display_backend(db_session, field, form, current_user):
    """ Executes one fields backend code before_display() """
    tag = field.field_type.tag
    # field_py_file_path = f"backend/fields/{tag}.py"
    function_name = "before_display"

    # if os.path.exists(ax_misc.path(field_py_file_path)):
    field_py = globals().get(f'AxField{tag}', None)
    if field_py and hasattr(field_py, function_name):
        method_to_call = getattr(field_py, function_name)
        new_value = await method_to_call(
            db_session=db_session,
            field=field,
            form=form,
            current_user=current_user)
        return new_value
    return field.value


async def execute_before_display(db_session, ax_form, current_user):
    """ for each field - execute before_display() if needed """
    for field in ax_form.no_tab_fields:
        if field.field_type.is_display_backend_avalible:
            field.value = await exec_display_backend(
                db_session=db_session,
                field=field,
                form=ax_form,
                current_user=current_user)
    return ax_form


async def set_form_values(db_session, ax_form, row_guid, current_user):
    """ Select row from DB and set AxForm.fields values, state and rowGuid

    Args:
        ax_form (AxForm): empty AxForm, without field values
        row_guid (str): Guid or AxNum of row

    Returns:
        AxForm: Form with field values
    """

    result = await ax_dialects.dialect.select_one(
        db_session=db_session,
        form=ax_form,
        fields_list=ax_form.db_fields,
        row_guid=row_guid)

    if result:
        ax_form.current_state_name = result[0]['axState']
        ax_form.row_guid = result[0]['guid']

        # populate each AxField with data
        for field in ax_form.no_tab_fields:
            if field in ax_form.db_fields or field.field_type.is_virtual:
                if field.is_virtual:
                    field.value = result[0][field.field_type.virtual_source]
                else:
                    field.value = await ax_dialects.dialect.get_value(
                        type_name=field.field_type.value_type,
                        value=result[0][field.db_name])

                if field.field_type.is_display_backend_avalible:
                    field.value = await exec_display_backend(
                        db_session=db_session,
                        field=field,
                        form=ax_form,
                        current_user=current_user)

    return ax_form


class CreateTab(graphene.Mutation):
    """ Creates AxField wich is tab """
    class Arguments:  # pylint: disable=missing-docstring
        form_guid = graphene.String()
        name = graphene.String()

    ok = graphene.Boolean()
    field = graphene.Field(Field)

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = f"Error in gql mutation - form.schema -> CreateTab"
        with ax_model.try_catch(info.context['session'], err) as db_session:
            form_guid = args.get('form_guid')
            name = args.get('name')

            ax_form = db_session.query(AxForm).filter(
                AxForm.guid == uuid.UUID(form_guid)
            ).first()

            ax_field = AxField()
            ax_field.name = name
            ax_field.form_guid = ax_form.guid
            ax_field.is_tab = True
            ax_field.position = len(
                [i for i in ax_form.fields if i.is_tab is True]) + 1
            db_session.add(ax_field)
            db_session.flush()
            ok = True
            return CreateTab(field=ax_field, ok=ok)


class UpdateTab(graphene.Mutation):
    """ Updates AxField witch is tab """
    class Arguments:  # pylint: disable=missing-docstring
        guid = graphene.String()    # AxField guid
        name = graphene.String()    # new name

    ok = graphene.Boolean()
    field = graphene.Field(Field)

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = 'Error in gql mutation - form_schema -> UpdateTab.'
        with ax_model.try_catch(info.context['session'], err) as db_session:
            guid = args.get('guid')
            name = args.get('name')

            ax_field = db_session.query(AxField).filter(
                AxField.guid == uuid.UUID(guid)
            ).first()
            ax_field.name = name
            db_session.flush()
            ok = True
            return UpdateTab(field=ax_field, ok=ok)


class DeleteTab(graphene.Mutation):
    """ Deletes AxField witch is tab """
    class Arguments:  # pylint: disable=missing-docstring
        guid = graphene.String()

    ok = graphene.Boolean()
    deleted = graphene.String()

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = 'Error in gql mutation - form_schema -> DeleteTab.'
        with ax_model.try_catch(info.context['session'], err) as db_session:
            guid = args.get('guid')
            ax_field = db_session.query(AxField).filter(
                AxField.guid == uuid.UUID(guid)
            ).first()
            db_session.delete(ax_field)
            return DeleteTab(deleted=guid, ok=True)


class CreateField(graphene.Mutation):
    """ Creates AxField

    Arguments:
        form_guid (str): Guid of AxForm
        name (str): Name of new field. Default from en.json
        tag (str): Tag of created field type. Example - AxNum or AxString
        positions (List(PositionInput)): List of positions for all fields
            of form. When field added, we must change position of all fields
            that are lower then inserted.
        position (int): Position of created field
        parent (str): Guid of tab (AxField) wich is parent to current field

    Returns:
        field: Created AxField
        permissions: Default admin permissions that were created. Used to
            update vuex store of workflow constructor.
    """
    class Arguments:  # pylint: disable=missing-docstring
        form_guid = graphene.String()
        name = graphene.String()
        tag = graphene.String()
        positions = graphene.List(
            PositionInput, required=False, default_value=None)
        position = graphene.Int(required=False, default_value=None)
        parent = graphene.String(required=False, default_value=None)

    ok = graphene.Boolean()
    field = graphene.Field(Field)
    roles = graphene.List(Role)

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        import backend.schema as ax_schema
        err = 'Error in gql mutation - form_schema -> CreateTab'
        with ax_model.try_catch(info.context['session'], err) as db_session:
            current_user = info.context['user']

            form_guid = args.get('form_guid')
            name = args.get('name')
            tag = args.get('tag')
            position = args.get('position')
            positions = args.get('positions')
            parent = args.get('parent')

            cur_name = None
            cur_db_name = None
            name_is_checked = False
            cur_num = 1

            ax_field_type = db_session.query(AxFieldType).filter(
                AxFieldType.tag == tag
            ).first()

            ax_form = db_session.query(AxForm).filter(
                AxForm.guid == uuid.UUID(form_guid)
            ).first()

            # If db table already have {db_name} column -> add digit to db_name
            while name_is_checked is False:
                error_flag = False
                if cur_num > 1:
                    cur_name = name + " " + str(cur_num)
                    cur_db_name = ax_field_type.default_db_name + str(cur_num)
                else:
                    cur_name = name
                    cur_db_name = ax_field_type.default_db_name

                for field in ax_form.fields:
                    if field.name == cur_name or field.db_name == cur_db_name:
                        error_flag = True

                if error_flag is True:
                    cur_num = cur_num + 1
                else:
                    name_is_checked = True
                    break

            if not positions:
                positions = []
            if not parent:
                for fld in ax_form.fields:
                    if fld.is_tab and not parent:
                        parent = fld.guid
            if not position:
                flds_num = 0
                for fld in ax_form.fields:
                    if str(fld.parent) == str(parent):
                        flds_num += 1
                position = flds_num

            ax_field = AxField()
            ax_field.name = cur_name
            ax_field.db_name = cur_db_name
            ax_field.form_guid = ax_form.guid
            ax_field.value_type = ax_field_type.value_type
            ax_field.field_type_tag = ax_field_type.tag
            ax_field.options_json = "{}"
            ax_field.position = position
            ax_field.parent = ax_misc.guid_or_none(parent)

            if ax_field_type.is_always_whole_row:
                ax_field.is_whole_row = True

            db_session.add(ax_field)

            if not ax_field_type.is_virtual:
                await ax_dialects.dialect.add_column(
                    db_session=db_session,
                    table=ax_form.db_name,
                    db_name=ax_field.db_name,
                    type_name=ax_field_type.value_type)

            db_session.flush()

            # Update positions of all fields that are lower then created field
            for field in ax_form.fields:
                for pos in positions:
                    if field.guid == uuid.UUID(pos.guid):
                        current_parent = None
                        if pos.parent != '#':
                            current_parent = uuid.UUID(pos.parent)
                        field.position = pos.position
                        field.parent = current_parent

            # Run after_create if needed
            if ax_field.field_type.is_backend_available:
                tag = ax_field.field_type_tag
                field_py = globals().get(f'AxField{tag}', None)
                if field_py and hasattr(field_py, "after_field_create"):
                    method_to_call = getattr(field_py, "after_field_create")
                    await method_to_call(
                        db_session=db_session,
                        field=ax_field,
                        before_form=ax_form,
                        tobe_form=ax_form,
                        action=None,
                        current_user=current_user)

            db_session.commit()
            ax_schema.init_schema(db_session)  # re-create GQL schema
            roles = ax_form.roles

            ok = True
            return CreateField(field=ax_field, roles=roles, ok=ok)


class UpdateField(graphene.Mutation):
    """ Updates AxField

    Arguments:
        guid (str): Guid of AxField that needs update
        name (str): New field name
        db_name (str): New db_name of field
        is_required (bool): Is field required
        is_whole_row (bool): Is field always displayed in whole row
        options_json (JSONString): Json wich is transformed to dict by graphene.
            Contains public field options that are passed to vue
        private_options_json (JSONString): Contains options that are visible
            only in python backend actions. Not visible in Vue.

    Returns:
        field (AxField): Created field

    """
    class Arguments:  # pylint: disable=missing-docstring
        guid = graphene.String()
        name = graphene.String()
        db_name = graphene.String()
        is_required = graphene.Boolean(required=False, default_value=None)
        is_whole_row = graphene.Boolean(required=False, default_value=None)
        options_json = graphene.JSONString(required=False, default_value=None)
        private_options_json = graphene.JSONString(
            required=False, default_value=None)

    ok = graphene.Boolean()
    field = graphene.Field(Field)

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        import backend.schema as ax_schema
        err = 'Error in gql mutation - form_schema -> UpdateField.'
        with ax_model.try_catch(info.context['session'], err) as db_session:
            guid = args.get('guid')
            name = args.get('name')
            db_name = args.get('db_name')
            is_required = args.get('is_required')
            is_whole_row = args.get('is_whole_row')
            options_json = args.get('options_json')
            private_options_json = args.get('private_options_json')

            schema_needs_update = False

            ax_field = db_session.query(AxField).filter(
                AxField.guid == uuid.UUID(guid)
            ).first()

            if name:
                ax_field.name = name

            if db_name and db_name != ax_field.db_name:
                db_name_error = False
                for field in ax_field.form.fields:
                    if field.db_name == db_name and (
                            field.guid != uuid.UUID(guid)):
                        db_name_error = True

                if db_name_error:
                    db_name = db_name + '_enother'

                await ax_dialects.dialect.rename_column(
                    db_session=db_session,
                    table=ax_field.form.db_name,
                    old_name=ax_field.db_name,
                    new_name=db_name,
                    type_name=ax_field.field_type.value_type
                )

                ax_field.db_name = db_name
                db_session.flush()
                schema_needs_update = True

            if options_json:
                ax_field.options_json = json.dumps(options_json)

            if private_options_json:
                ax_field.private_options_json = json.dumps(
                    private_options_json)

            if is_required is not None:
                ax_field.is_required = is_required

            if is_whole_row is not None:
                if ax_field.field_type.is_always_whole_row:
                    ax_field.is_whole_row = True
                else:
                    ax_field.is_whole_row = is_whole_row

            # db_session.flush()

            if schema_needs_update:
                ax_schema.init_schema(db_session)  # re-create GQL schema

            ok = True
            return CreateTab(field=ax_field, ok=ok)


class DeleteField(graphene.Mutation):
    """ Deletes AxField """
    class Arguments:  # pylint: disable=missing-docstring
        guid = graphene.String()

    ok = graphene.Boolean()
    roles = graphene.List(Role)
    deleted = graphene.String()

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        import backend.schema as ax_schema
        err = 'Error in gql mutation - form_schema -> DeleteField.'
        with ax_model.try_catch(info.context['session'], err) as db_session:
            current_user = info.context['user']
            guid = args.get('guid')

            ax_field = db_session.query(AxField).filter(
                AxField.guid == uuid.UUID(guid)
            ).first()

            db_session.query(AxRoleFieldPermission).filter(
                AxRoleFieldPermission.field_guid == ax_field.guid).delete()
            db_session.query(AxColumn).filter(
                AxColumn.field_guid == ax_field.guid).delete()

            if ax_field.is_tab is False and ax_field.is_virtual is False:
                await ax_dialects.dialect.drop_column(
                    db_session=db_session,
                    table=ax_field.form.db_name,
                    column=ax_field.db_name
                )

            # if backend avalible
            if ax_field.field_type.is_backend_available:
                tag = ax_field.field_type_tag
                field_py = globals().get(f'AxField{tag}', None)
                if field_py and hasattr(field_py, "before_field_delete"):
                    method_to_call = getattr(field_py, "before_field_delete")
                    await method_to_call(
                        db_session=db_session,
                        field=ax_field,
                        before_form=ax_field.form,
                        tobe_form=ax_field.form,
                        action=None,
                        current_user=current_user)

            roles = ax_field.form.roles
            db_session.delete(ax_field)
            ax_schema.init_schema(db_session)  # re-create GQL schema

            ok = True
            return DeleteField(deleted=guid, roles=roles, ok=ok)


class ChangeFieldsPositions(graphene.Mutation):
    """Change position and parent of multiple fields"""
    class Arguments:  # pylint: disable=missing-docstring
        form_guid = graphene.String()
        positions = graphene.List(PositionInput)  # positions of all fields

    ok = graphene.Boolean()
    fields = graphene.List(Field)

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = 'Error in gql mutation - form_schema -> ChangeFieldsPositions.'
        with ax_model.try_catch(info.context['session'], err) as db_session:
            form_guid = args.get('form_guid')
            positions = args.get('positions')

            ax_form = db_session.query(AxForm).filter(
                AxForm.guid == uuid.UUID(form_guid)
            ).one()

            for field in ax_form.fields:
                for position in positions:
                    if field.guid == uuid.UUID(position.guid):
                        current_parent = None
                        if position.parent != '#':
                            current_parent = uuid.UUID(position.parent)
                        field.parent = current_parent
                        field.position = position.position

            # db_session.flush()
            query = Field.get_query(info)
            field_list = query.filter(
                AxField.form_guid == uuid.UUID(form_guid)
            ).all()
            return ChangeFieldsPositions(fields=field_list, ok=True)


class FormQuery(graphene.ObjectType):
    """Query all data of AxForm and related classes"""
    # all_fields = graphene.List(Field, form_field=graphene.String())
    ax_form = graphene.Field(
        Form,
        db_name=graphene.Argument(type=graphene.String, required=True),
        update_time=graphene.Argument(type=graphene.String, required=False)
    )
    form_data = graphene.Field(
        Form,
        db_name=graphene.Argument(type=graphene.String, required=True),
        row_guid=graphene.Argument(type=graphene.String, required=False),
        update_time=graphene.Argument(type=graphene.String, required=False)
    )

    async def resolve_ax_form(self, info, db_name=None, update_time=None):
        """ Get AxForm by db_name

        Args:
            db_name (str, optional): AxForm db_name. Defaults to None.
            update_time (str, optional): Used to disable gql caching.

        Returns:
            AxForm: AxForm
        """
        del update_time
        err = 'form_schema -> resolve_form'
        with ax_model.try_catch(
                info.context['session'], err, no_commit=True):
            query = Form.get_query(info=info)
            result = query.filter(AxForm.db_name == db_name)
            # return None
            ret_result = None
            if result:
                ret_result = result.first()
            return ret_result

    async def resolve_form_data(
            self, info, db_name=None, row_guid=None, update_time=None):
        """ Get AxForm by db_name and row guid

        Args:
            db_name (str, optional): AxForm db_name. Defaults to None.
            row_guid (str, optional): Guid of table row or AxNum value.
            update_time (str, optional): Used to disable gql caching.

        Returns:
            AxForm: Form with field values, avaluble actions, state, row_guid
        """
        current_user = info.context['user']
        err = 'Error in gql query - form_schema -> resolve_form_data'
        with ax_model.try_catch(
                info.context['session'], err, no_commit=True) as db_session:
            del update_time  # used to disable gql caching

            query = Form.get_query(info=info)
            ax_form = query.filter(AxForm.db_name == db_name).first()

            if not ax_form:
                return None

            if row_guid is not None:
                ax_form = await set_form_values(
                    db_session=db_session,
                    ax_form=ax_form,
                    row_guid=row_guid,
                    current_user=current_user)

            ax_form = await execute_before_display(
                db_session=db_session,
                ax_form=ax_form,
                current_user=current_user)

            state_guid = await ax_auth.get_state_guid(
                ax_form=ax_form,
                state_name=ax_form.current_state_name)

            # Check if form have dynamic role
            dynamic_role_guids = await ax_auth.get_dynamic_roles_guids(
                ax_form=ax_form,
                current_user=current_user)

            ax_form.avalible_actions = await action_schema.get_actions(
                form=ax_form,
                current_state=ax_form.current_state_name,
                current_user=current_user,
                dynamic_role_guids=dynamic_role_guids
            )

            ax_form = await ax_auth.set_form_visibility(
                ax_form=ax_form,
                state_guid=state_guid,
                current_user=current_user,
                dynamic_role_guids=dynamic_role_guids)

            return ax_form


class FormMutations(graphene.ObjectType):
    """Combine all mutations"""
    create_tab = CreateTab.Field()
    update_tab = UpdateTab.Field()
    delete_tab = DeleteTab.Field()
    create_field = CreateField.Field()
    update_field = UpdateField.Field()
    delete_field = DeleteField.Field()
    change_fields_positions = ChangeFieldsPositions.Field()
