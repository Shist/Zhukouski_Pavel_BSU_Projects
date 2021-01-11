""" This is part of GraphQL schema (Mutaions, Queryes, Subscriptions).
Defines manipulation with Grids - create/update/delete of AxGrid and AxColumn
Mutation and queryes used only by constructor. AxGrid uses dynamic GQL schema.
Sea schema.py for more info.
"""
import uuid
import json
import graphene
from backend.model import AxForm, AxGrid, AxColumn, AxField
import backend.dialects as ax_dialects
import backend.model as ax_model


# import backend.cache as ax_cache # TODO use cache!
from backend.schemas.types import Grid, Column, PositionInput
from backend.auth import ax_admin_only


def get_default_grid_code():
    """ Returns default code for grid.
        Used in createTable (grids_schema)
        and createForm (home_schema)  """
    code = f"""ax.query = f\"\"\"
    {ax_dialects.default_grid_query}
\"\"\""""
    return code


def tom_sync_grid(db_session, form_db_name, old_db_name, new_db_name):
    """ Relation fields such as Ax1to1, Ax1tom and Ax1tomTable are using
    options_json to store db_name of grid used. If grid db_name is changed,
    the Json's in every relation field must be updated.
    For each relation field - check if options contain old form and old grid.

    Args:
        form_db_name (str): Current form db_name
        old_db_name (str): Old db_name of grid
        new_db_name (str): New db_name of grid
    """
    relation_fields = db_session.query(AxField).filter(
        AxField.field_type_tag.in_(('Ax1to1', 'Ax1tom', 'Ax1tomTable'))
    ).all()
    for field in relation_fields:
        if 'form' in field.options.keys() and 'grid' in field.options.keys():
            if field.options['grid'] == old_db_name and \
                    field.options['form'] == form_db_name:

                new_options = field.options
                new_options['grid'] = new_db_name

                field.options_json = json.dumps(new_options)
                db_session.flush()


class CreateColumn(graphene.Mutation):
    """ Creates AxColumn

    Arguments:
        grid_guid (str): Guid of AxGrid
        field_guid (str): Guid of AxField
        column_type (str): Not used!. Was used for responsive grid. #TODO delete
        position (int): Position of column in grid
        positions (List(PositionInput)): Position of other columns in grid

    Returns:
        column (AxColumn): Created grid column
    """
    class Arguments:  # pylint: disable=missing-docstring
        grid_guid = graphene.String()
        field_guid = graphene.String()
        column_type = graphene.String(required=False, default_value=None)
        position = graphene.Int(required=False, default_value=None)
        positions = graphene.List(
            PositionInput, required=False, default_value=None)

    ok = graphene.Boolean()
    column = graphene.Field(Column)

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = 'grids_schema -> CreateColumn'
        with ax_model.try_catch(info.context['session'], err) as db_session:
            grid_guid = args.get('grid_guid')
            field_guid = args.get('field_guid')
            column_type = args.get('column_type')
            position = args.get('position')
            positions = args.get('positions')

            ax_grid = db_session.query(AxGrid).filter(
                AxGrid.guid == uuid.UUID(grid_guid)
            ).first()

            if not positions:
                positions = []
            if not position:
                position = len(ax_grid.columns)

            ax_column = AxColumn()
            ax_column.grid_guid = ax_grid.guid
            ax_column.field_guid = uuid.UUID(field_guid)
            ax_column.column_type = column_type
            ax_column.position = position
            db_session.add(ax_column)

            for column in ax_grid.columns:
                for pos in positions:
                    if str(column.guid) == pos.guid:
                        column.position = pos.position
                        column.column_type = pos.parent

            db_session.flush()
            return CreateColumn(column=ax_column, ok=True)


class UpdateColumnOptions(graphene.Mutation):
    """Updates options of column"""
    class Arguments:  # pylint: disable=missing-docstring
        guid = graphene.String()
        options = graphene.String()

    ok = graphene.Boolean()

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = 'Error in gql mutation - grids_schema -> UpdateColumnOptions.'
        with ax_model.try_catch(info.context['session'], err) as db_session:
            ax_column = db_session.query(AxColumn).filter(
                AxColumn.guid == uuid.UUID(args.get('guid'))
            ).first()
            ax_column.options_json = args.get('options')
            db_session.flush()
            return UpdateColumnOptions(ok=True)


class DeleteColumn(graphene.Mutation):
    """ Deletes AxColumn """
    class Arguments:  # pylint: disable=missing-docstring
        guid = graphene.String()

    ok = graphene.Boolean()
    deleted = graphene.String()

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = 'Error in gql mutation - grids_schema -> DeleteColumn'
        with ax_model.try_catch(info.context['session'], err) as db_session:
            guid = args.get('guid')
            ax_column = db_session.query(AxColumn).filter(
                AxColumn.guid == uuid.UUID(guid)
            ).first()
            db_session.delete(ax_column)
            return DeleteColumn(deleted=guid, ok=True)


class ChangeColumnsPositions(graphene.Mutation):
    """Change position and type of columns"""
    class Arguments:  # pylint: disable=missing-docstring
        grid_guid = graphene.String()
        positions = graphene.List(PositionInput)

    ok = graphene.Boolean()
    columns = graphene.List(Column)

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = 'Error in gql mutation - grids_schema -> ChangeColumnsPositions.'
        with ax_model.try_catch(info.context['session'], err) as db_session:
            grid_guid = args.get('grid_guid')
            positions = args.get('positions')

            ax_grid = db_session.query(AxGrid).filter(
                AxGrid.guid == uuid.UUID(grid_guid)
            ).one()

            for column in ax_grid.columns:
                for pos in positions:
                    if column.guid == uuid.UUID(pos.guid):
                        column.position = pos.position
                        column.column_type = pos.parent
            db_session.flush()
            query = Column.get_query(info)
            column_list = query.filter(
                AxColumn.grid_guid == uuid.UUID(grid_guid)
            ).all()

            ok = True
            return ChangeColumnsPositions(columns=column_list, ok=ok)


class CreateGrid(graphene.Mutation):
    """ Creates AxGrid """
    class Arguments:  # pylint: disable=missing-docstring
        form_guid = graphene.String()
        name = graphene.String()

    ok = graphene.Boolean()
    grid = graphene.Field(Grid)

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        import backend.schema as ax_schema
        err = 'Error in gql mutation - grids_schema -> CreateGrid.'
        with ax_model.try_catch(info.context['session'], err) as db_session:
            form_guid = args.get('form_guid')
            name = args.get('name')

            ax_form = db_session.query(AxForm).filter(
                AxForm.guid == uuid.UUID(form_guid)
            ).first()

            db_name = "Grid"
            cur_num = 1
            name_is_checked = False
            while name_is_checked is False:
                error_flag = False
                if cur_num > 1:
                    cur_name = name + " " + str(cur_num)
                else:
                    cur_name = name
                cur_db_name = db_name + str(cur_num)
                for grid in ax_form.grids:
                    if grid.name == cur_name or grid.db_name == cur_db_name:
                        error_flag = True
                if error_flag is True:
                    cur_num = cur_num + 1
                else:
                    name_is_checked = True
                    break

            ax_grid = AxGrid()
            ax_grid.name = cur_name
            ax_grid.db_name = db_name + str(cur_num)
            ax_grid.form_guid = ax_form.guid
            ax_grid.code = None
            ax_grid.position = len(ax_form.grids) + 1

            default_options = {
                "enableQuickSearch": False,
                "enableFlatMode": False,
                "enableColumnsResize": True,
                "enableFiltering": True,
                "enableSorting": True,
                "enableOpenForm": True,
                "enableActions": True,
                "rowHeight": 45,
                "pinned": 0
            }

            ax_grid.options_json = json.dumps(default_options)
            ax_grid.is_default_view = False
            db_session.add(ax_grid)
            db_session.commit()
            ax_schema.init_schema(db_session)
            return CreateGrid(grid=ax_grid, ok=True)


class DeleteGrid(graphene.Mutation):
    """ Deletes AxFGrid """
    class Arguments:  # pylint: disable=missing-docstring
        guid = graphene.String()

    ok = graphene.Boolean()
    deleted = graphene.String()

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        import backend.schema as ax_schema
        err = 'Error in gql mutation - grids_schema -> DeleteGrid.'
        with ax_model.try_catch(info.context['session'], err) as db_session:
            guid = args.get('guid')

            ax_grid = db_session.query(AxGrid).filter(
                AxGrid.guid == uuid.UUID(guid)
            ).first()
            form_db_name = ax_grid.form.name
            old_grid_db_name = ax_grid.db_name
            default_db_name = None

            for grid in ax_grid.form.grids:
                if grid.is_default_view:
                    default_db_name = grid.db_name

            db_session.delete(ax_grid)
            db_session.commit()
            ax_schema.init_schema(db_session)
            tom_sync_grid(db_session=db_session,
                          form_db_name=form_db_name,
                          old_db_name=old_grid_db_name,
                          new_db_name=default_db_name)
            return DeleteGrid(deleted=guid, ok=True)


class UpdateGrid(graphene.Mutation):
    """ Update AxGrid """
    class Arguments:  # pylint: disable=missing-docstring
        guid = graphene.String()
        name = graphene.String()
        db_name = graphene.String()
        options_json = graphene.String()
        is_default_view = graphene.Boolean()

    ok = graphene.Boolean()
    grid = graphene.Field(Grid)

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        import backend.schema as ax_schema
        err = 'Error in gql mutation - grids_schema -> UpdateGrid.'
        with ax_model.try_catch(info.context['session'], err) as db_session:
            guid = args.get('guid')
            name = args.get('name')
            db_name = args.get('db_name')
            options_json = args.get('options_json')
            is_default_view = args.get('is_default_view')
            schema_reload_needed = False
            tom_sync_needed = False

            ax_grid = db_session.query(AxGrid).filter(
                AxGrid.guid == uuid.UUID(guid)
            ).first()
            old_db_name = ax_grid.db_name

            if name:
                ax_grid.name = name

            if db_name:
                ax_grid.db_name = db_name
                schema_reload_needed = True
                if old_db_name != db_name:
                    tom_sync_needed = True

            if options_json:
                ax_grid.options_json = options_json

            if is_default_view:
                all_grids = db_session.query(AxGrid).filter(
                    AxGrid.form_guid == ax_grid.form_guid
                    and AxGrid.guid != ax_grid.guid
                ).all()

                for grid in all_grids:
                    grid.is_default_view = False

                ax_grid.is_default_view = is_default_view
                schema_reload_needed = True

            db_session.commit()

            if schema_reload_needed:
                ax_schema.init_schema(db_session)

            if tom_sync_needed:
                tom_sync_grid(
                    db_session=db_session,
                    form_db_name=ax_grid.form.db_name,
                    old_db_name=old_db_name,
                    new_db_name=ax_grid.db_name)

            return UpdateGrid(grid=ax_grid, ok=True)


class UpdateGridCode(graphene.Mutation):
    """ Update code of AxGrid """
    class Arguments:  # pylint: disable=missing-docstring
        guid = graphene.String()
        code = graphene.String()

    ok = graphene.Boolean()

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = 'Error in gql mutation - grids_schema -> UpdateGridCode.'
        with ax_model.try_catch(info.context['session'], err) as db_session:
            guid = args.get('guid')
            code = args.get('code')

            ax_grid = db_session.query(AxGrid).filter(
                AxGrid.guid == uuid.UUID(guid)
            ).first()

            if code is None or code == get_default_grid_code() or code == '':
                ax_grid.code = None
            else:
                ax_grid.code = code

            db_session.commit()
            return UpdateGridCode(ok=True)


class GridsQuery(graphene.ObjectType):
    """Query all data of AxGrid and related classes"""
    ax_grid = graphene.Field(
        Grid,
        form_db_name=graphene.Argument(type=graphene.String, required=True),
        grid_db_name=graphene.Argument(type=graphene.String, required=True),
        update_time=graphene.Argument(type=graphene.String, required=False)
    )
    grids_list = graphene.List(
        Grid,
        form_db_name=graphene.Argument(type=graphene.String, required=True),
        update_time=graphene.Argument(type=graphene.String, required=False)
    )

    async def resolve_ax_grid(
            self, info, form_db_name, grid_db_name, update_time=None):
        """Get AxGrid by form db_name and grid db_name"""
        del update_time
        err = 'grids_schema -> resolve_grid'
        with ax_model.try_catch(
                info.context['session'], err, no_commit=True) as db_session:
            grid = None
            ax_form = db_session.query(AxForm).filter(
                AxForm.db_name == form_db_name
            ).first()

            if ax_form:
                query = Grid.get_query(info=info)
                if grid_db_name and grid_db_name != 'null':
                    grid = query.filter(
                        AxGrid.form_guid == ax_form.guid
                    ).filter(
                        AxGrid.db_name == grid_db_name
                    ).first()
                else:
                    grid = query.filter(
                        AxGrid.form_guid == ax_form.guid
                    ).filter(
                        AxGrid.is_default_view.is_(True)
                    ).first()

                if not grid or not grid.code:
                    grid.code_not_none = get_default_grid_code()
                else:
                    grid.code_not_none = grid.code
            return grid

    @ax_admin_only
    async def resolve_grids_list(self, info, form_db_name):
        """Gets list of all AxGrid's of form """
        err = 'grids_schema -> resolve_grids_list'
        with ax_model.try_catch(
                info.context['session'], err, no_commit=True) as db_session:
            ax_form = db_session.query(AxForm).filter(
                AxForm.db_name == form_db_name
            ).first()

            query = Grid.get_query(info=info)
            grids = query.filter(AxGrid.form_guid == ax_form.guid).all()
            return grids


class GridsMutations(graphene.ObjectType):
    """Combine all mutations"""
    create_column = CreateColumn.Field()
    delete_column = DeleteColumn.Field()
    change_columns_positions = ChangeColumnsPositions.Field()
    create_grid = CreateGrid.Field()
    delete_grid = DeleteGrid.Field()
    update_grid = UpdateGrid.Field()
    update_grid_code = UpdateGridCode.Field()
