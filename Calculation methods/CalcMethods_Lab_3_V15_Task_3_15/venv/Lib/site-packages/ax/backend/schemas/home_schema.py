"""Describes schema for AxForm manipulation in admin home
Create/update/delete of Form, Folder """
import uuid
import os
import shutil
import json
from sqlalchemy import MetaData
import graphene
from loguru import logger
from graphene_sqlalchemy.converter import convert_sqlalchemy_type
from backend.misc import convert_column_to_string  # TODO check if needed
from backend.model import GUID, AxForm, AxField, AxGrid, AxAction, AxState, \
    AxRole2Users, AxRoleFieldPermission, AxState2Role, AxAction2Role, \
    Ax1tomReference
import backend.model as ax_model
# import backend.cache as ax_cache
import backend.dialects as ax_dialects
import backend.misc as ax_misc
import backend.auth as ax_auth
from backend.schemas.types import Form, PositionInput, LicenseInfo
from backend.auth import ax_admin_only

convert_sqlalchemy_type.register(GUID)(convert_column_to_string)


async def tom_sync_form(db_session, old_form_db_name, new_form_db_name):
    """ Relation fields such as Ax1to1, Ax1tom, Ax1tomTable,
    Ax1to1Children are using
    options_json to store db_name of related form. If form db_name is changed,
    the Json's in every relation field must be updated.
    For each relation field - check if options contain old form name and update.

    Args:
        old_form_db_name (str): Old db_name of form
        new_form_db_name (str): New db_name of form
    """
    relation_fields = db_session.query(AxField).filter(
        AxField.field_type_tag.in_(
            ('Ax1to1', 'Ax1tom', 'Ax1tomTable', 'Ax1to1Children'))
    ).all()
    for field in relation_fields:
        if 'form' in field.options.keys() and 'grid' in field.options.keys():
            if field.options['form'] == old_form_db_name:
                new_options = field.options
                new_options['form'] = new_form_db_name
                field.options_json = json.dumps(new_options)
                db_session.flush()


async def is_db_name_avalible(db_name) -> bool:
    """Check if table with name '_db_name' is already exists in database"""
    try:
        meta = MetaData()
        meta.reflect(bind=ax_model.engine)
        db_names = list(meta.tables.keys())
        return db_name not in db_names
    except Exception:
        logger.exception('Error checking if db_name exists in database.')
        raise


async def create_db_table(db_session, db_name) -> None:
    """Create database table"""
    try:
        await ax_dialects.dialect.create_data_table(
            db_session=db_session,
            db_name=db_name)
    except Exception:
        logger.exception('Error creating new Form. Cant create db table')
        raise


async def create_ax_form(db_session, name, db_name) -> object:
    """Creates AxForm object"""
    err = "home_schema -> create_ax_form"
    with ax_model.try_catch(db_session, err) as db_session:
        ax_form = AxForm()
        ax_form.name = name
        ax_form.db_name = db_name
        ax_form.tom_label = "{{guid}}"
        ax_form.icon = "dice-d6"  # TODO: move default icon to Vue
        db_session.add(ax_form)
        db_session.flush()
        return ax_form


async def create_default_tab(db_session, ax_form, name) -> None:
    """ Create default AxForm tab """
    err = "home_schema -> create_default_tab"
    with ax_model.try_catch(db_session, err) as db_session:
        ax_field = AxField()
        ax_field.name = name
        ax_field.form_guid = ax_form.guid
        ax_field.is_tab = True
        ax_field.position = 1
        db_session.add(ax_field)
        db_session.flush()


async def create_default_grid(db_session, ax_form, name):
    """Creates default AxGrid"""
    err = "home_schema -> create_default_grid"
    with ax_model.try_catch(db_session, err) as db_session:
        ax_grid = AxGrid()
        ax_grid.name = name
        ax_grid.db_name = 'Default'
        ax_grid.form_guid = ax_form.guid
        ax_grid.code = None
        ax_grid.position = 1

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
        ax_grid.is_default_view = True
        db_session.add(ax_grid)
        db_session.flush()


async def create_default_states(db_session,
                                ax_form,
                                default_start,
                                default_state,
                                default_all,
                                default_deleted):
    """Creates default AxStates"""
    err = "home_schema -> create_default_states"
    with ax_model.try_catch(db_session, err) as db_session:
        start = AxState()
        start.name = default_start
        start.form_guid = ax_form.guid
        start.x = 0
        start.y = -200
        start.is_start = True
        db_session.add(start)

        created = AxState()
        created.name = default_state
        created.form_guid = ax_form.guid
        created.x = 0
        created.y = 0
        db_session.add(created)

        deleted = AxState()
        deleted.name = default_deleted
        deleted.form_guid = ax_form.guid
        deleted.x = 0
        deleted.y = 200
        deleted.is_deleted = True
        db_session.add(deleted)

        all_state = AxState()
        all_state.name = default_all
        all_state.form_guid = ax_form.guid
        all_state.x = 300
        all_state.y = 20
        all_state.is_all = True
        db_session.add(all_state)
        db_session.flush()

        return {
            "start": start.guid,
            "created": created.guid,
            "deleted": deleted.guid
        }


async def create_default_actions(
        db_session, ax_form, states, default_create, default_delete,
        default_update, delete_confirm):
    """Creates default AxActions"""
    err = "home_schema -> create_default_actions"
    with ax_model.try_catch(db_session, err) as db_session:
        create = AxAction()
        create.name = default_create
        create.form_guid = ax_form.guid
        create.from_state_guid = states['start']
        create.to_state_guid = states['created']
        db_session.add(create)

        update = AxAction()
        update.name = default_update
        update.form_guid = ax_form.guid
        update.from_state_guid = states['created']
        update.to_state_guid = states['created']
        db_session.add(update)

        delete = AxAction()
        delete.name = default_delete
        delete.form_guid = ax_form.guid
        delete.from_state_guid = states['created']
        delete.to_state_guid = states['deleted']
        delete.confirm_text = delete_confirm
        db_session.add(delete)
        db_session.flush()

        return {
            "create": create.guid,
            "delete": delete.guid
        }


class CreateForm(graphene.Mutation):
    """ Creates AxForm """
    class Arguments:  # pylint: disable=missing-docstring
        name = graphene.String()
        db_name = graphene.String()
        default_tab_name = graphene.String()
        default_grid_name = graphene.String()
        default_start = graphene.String()
        default_all = graphene.String()
        default_create = graphene.String()
        default_state = graphene.String()
        default_delete = graphene.String()
        default_deleted = graphene.String()
        default_update = graphene.String()
        delete_confirm = graphene.String()

    ok = graphene.Boolean()
    avalible = graphene.Boolean()
    form = graphene.Field(Form)

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        import backend.schema as ax_schema
        err = "home_schema -> CreateForm"
        with ax_model.try_catch(info.context['session'], err) as db_session:
            name = args.get('name')
            db_name = args.get('db_name')
            default_tab_name = args.get('default_tab_name')
            default_grid_name = args.get('default_grid_name')
            default_start = args.get('default_start')
            default_all = args.get('default_all')
            default_create = args.get('default_create')
            default_state = args.get('default_state')
            default_delete = args.get('default_delete')
            default_deleted = args.get('default_deleted')
            default_update = args.get('default_update')
            delete_confirm = args.get('delete_confirm')

            name_avalible = await is_db_name_avalible(db_name=db_name)
            if name_avalible is False:
                return CreateForm(form=None, avalible=False, ok=True)

            await create_db_table(
                db_session=db_session,
                db_name=db_name)

            new_form = await create_ax_form(
                db_session=db_session,
                name=name,
                db_name=db_name)

            # Add Admins role to object
            states = await create_default_states(
                db_session=db_session,
                ax_form=new_form,
                default_start=default_start,
                default_state=default_state,
                default_all=default_all,
                default_deleted=default_deleted)

            await create_default_actions(
                db_session=db_session,
                ax_form=new_form,
                states=states,
                default_create=default_create,
                default_delete=default_delete,
                default_update=default_update,
                delete_confirm=delete_confirm)

            await create_default_grid(
                db_session=db_session,
                ax_form=new_form,
                name=default_grid_name)

            await create_default_tab(
                db_session=db_session,
                ax_form=new_form,
                name=default_tab_name)

            db_session.commit()
            ax_schema.init_schema(db_session)
            # TODO: check for multiple workers and load balancers.
            # https://community.sanicframework.org/t/removing-routes-necessary-functionality/29

            return CreateForm(form=new_form, avalible=True, ok=True)


class UpdateForm(graphene.Mutation):
    """ Update AxForm """
    class Arguments:  # pylint: disable=missing-docstring
        guid = graphene.String()
        name = graphene.String()
        db_name = graphene.String()
        icon = graphene.String()
        tom_label = graphene.String()

    ok = graphene.Boolean()
    avalible = graphene.Boolean()
    db_name_changed = graphene.String()
    form = graphene.Field(Form)

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        import backend.schema as ax_schema
        err = "home_schema -> UpdateForm"
        with ax_model.try_catch(info.context['session'], err) as db_session:
            ax_form = db_session.query(AxForm).filter(
                AxForm.guid == uuid.UUID(args.get('guid'))
            ).first()
            old_form_db_name = ax_form.db_name
            db_name_changed = None
            tom_sync_needed = False
            schema_reload_needed = False

            if str(args.get('db_name')) != str(ax_form.db_name):
                db_name_changed = args.get('db_name')
                name_avalible = await is_db_name_avalible(
                    db_name=args.get('db_name'))
                if name_avalible is False:
                    return UpdateForm(
                        form=None,
                        avalible=False,
                        db_name_changed=None,
                        ok=True
                    )
                else:
                    await ax_dialects.dialect.rename_table(
                        db_session=db_session,
                        old=ax_form.db_name,
                        new=args.get('db_name'))
                    tom_sync_needed = True
                    schema_reload_needed = True

            ax_form.name = args.get('name')
            ax_form.db_name = args.get('db_name')
            ax_form.icon = args.get('icon')
            ax_form.tom_label = args.get('tom_label')
            db_session.flush()

            if schema_reload_needed:
                ax_schema.init_schema(db_session)

            if tom_sync_needed:
                await tom_sync_form(
                    db_session=db_session,
                    old_form_db_name=old_form_db_name,
                    new_form_db_name=ax_form.db_name)

            return UpdateForm(
                form=ax_form,
                avalible=True,
                db_name_changed=db_name_changed,
                ok=True
            )


class DeleteForm(graphene.Mutation):
    """-"""
    class Arguments:  # pylint: disable=missing-docstring
        guid = graphene.String()

    ok = graphene.Boolean()
    forms = graphene.List(Form)

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = "home_schema -> DeleteForm"
        with ax_model.try_catch(info.context['session'], err) as db_session:
            guid = args.get('guid')

            ax_form = db_session.query(AxForm).filter(
                AxForm.guid == uuid.UUID(guid)
            ).first()

            if not ax_form:
                return DeleteForm(forms=None, ok=False)

            # Remove objects connected to form - Ax1tomReference, AxRole2Users,
            # AxState2Role, AxAction2Role, AxRoleFieldPermission, AxRole,
            # AxAction, AxState, AxColumn, AxGrid, AxField

            db_session.query(Ax1tomReference).filter(
                Ax1tomReference.form_guid == ax_form.guid
            ).delete()

            for role in ax_form.roles:
                db_session.query(AxRole2Users).filter(
                    AxRole2Users.role_guid == role.guid).delete()
                db_session.query(AxState2Role).filter(
                    AxState2Role.role_guid == role.guid).delete()
                db_session.query(AxAction2Role).filter(
                    AxAction2Role.role_guid == role.guid).delete()
                db_session.query(AxRoleFieldPermission).filter(
                    AxRoleFieldPermission.role_guid == role.guid).delete()

                db_session.delete(role)

            for action in ax_form.actions:
                db_session.delete(action)

            for state in ax_form.states:
                db_session.delete(state)

            for grid in ax_form.grids:
                for column in grid.columns:
                    db_session.delete(column)
                db_session.delete(grid)

            for field in ax_form.fields:
                db_session.delete(field)

            await ax_dialects.dialect.drop_table(
                db_session=db_session, db_name=ax_form.db_name)

            db_session.delete(ax_form)
            db_session.flush()

            # s.execute("SET FOREIGN_KEY_CHECKS=1;")

            query = Form.get_query(info)  # SQLAlchemy query
            form_list = query.all()

            # Remove all uploaded files for this form
            uploads_path = ax_misc.path('uploads/form_row_field_file')
            form_folder = os.path.join(uploads_path, str(ax_form.guid))
            if os.path.exists(form_folder) is True:
                shutil.rmtree(form_folder)

            return DeleteForm(forms=form_list, ok=True)


class CreateFolder(graphene.Mutation):
    """ Creates AxForm wich is folder """
    class Arguments:  # pylint: disable=missing-docstring
        name = graphene.String()

    ok = graphene.Boolean()
    form = graphene.Field(Form)

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = "home_schema -> CreateFolder"
        with ax_model.try_catch(info.context['session'], err) as db_session:
            name = args.get('name')
            ax_form = AxForm()
            ax_form.name = name
            ax_form.is_folder = True
            db_session.add(ax_form)
            return CreateFolder(form=ax_form, ok=True)


class UpdateFolder(graphene.Mutation):
    """ Update AxForm wich is folder """
    class Arguments:  # pylint: disable=missing-docstring
        guid = graphene.String()
        name = graphene.String()

    ok = graphene.Boolean()
    form = graphene.Field(Form)

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = "home_schema -> UpdateFolder"
        with ax_model.try_catch(info.context['session'], err) as db_session:
            guid = args.get('guid')
            name = args.get('name')

            ax_form = db_session.query(AxForm).filter(
                AxForm.guid == uuid.UUID(guid)
            ).first()
            ax_form.name = name
            db_session.flush()
            return CreateFolder(form=ax_form, ok=True)


class DeleteFolder(graphene.Mutation):
    """ Delete AxForm wich is folder """
    class Arguments:  # pylint: disable=missing-docstring
        guid = graphene.String()

    forms = graphene.List(Form)
    ok = graphene.Boolean()

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = "home_schema -> DeleteFolder"
        with ax_model.try_catch(info.context['session'], err) as db_session:
            guid = args.get('guid')

            ax_folder = db_session.query(AxForm).filter(
                AxForm.guid == uuid.UUID(guid)
            ).first()

            sub_objects = db_session.query(AxForm).filter(
                AxForm.parent == ax_folder.guid
            ).all()

            for sub in sub_objects:
                sub.parent = None
                sub.position = 1000

            db_session.delete(ax_folder)
            db_session.flush()

            query = Form.get_query(info)  # SQLAlchemy query
            form_list = query.all()
            return DeleteFolder(forms=form_list, ok=True)


class ChangeFormsPositions(graphene.Mutation):
    """Change position and parent fields of multiple forms"""
    class Arguments:  # pylint: disable=missing-docstring
        positions = graphene.List(PositionInput)

    ok = graphene.Boolean()
    forms = graphene.List(Form)

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = "home_schema -> ChangeFormsPositions"
        with ax_model.try_catch(info.context['session'], err) as db_session:
            positions = args.get('positions')
            for position in positions:
                db_form = db_session.query(AxForm).filter(
                    AxForm.guid == uuid.UUID(position.guid)
                ).one()
                current_parent = None
                if position.parent != '#':
                    current_parent = uuid.UUID(position.parent)
                db_form.parent = current_parent
                db_form.position = position.position

            db_session.flush()

            query = Form.get_query(info)  # SQLAlchemy query
            form_list = query.all()
            return ChangeFormsPositions(forms=form_list, ok=True)


class HomeQuery(graphene.ObjectType):
    """AxForm queryes"""
    all_forms = graphene.List(
        Form,
        update_time=graphene.Argument(type=graphene.String, required=False)
    )
    sql_status = graphene.String()
    ping = graphene.String()
    ax_license_info = graphene.Field(
        LicenseInfo,
        update_time=graphene.Argument(type=graphene.String, required=False)
    )

    @ax_admin_only
    async def resolve_all_forms(self, info, update_time):
        """Get all users"""
        del update_time
        err = 'Error in GQL query - resolve_all_forms.'
        with ax_model.try_catch(
                info.context['session'], err, no_commit=True):
            query = Form.get_query(info)  # SQLAlchemy query
            form_list = query.all()
            return form_list

    async def resolve_sql_status(self, info):
        """ - """
        del info
        return ax_model.engine.pool.status()

    def resolve_ping(self, info):
        """ - """
        del info
        return "Pong"

    async def resolve_ax_license_info(self, info, update_time):
        """ Returns license info to be used in frontend """
        del update_time
        info = LicenseInfo(
            client_guid=ax_auth.client_guid,
            max_users=ax_auth.user_num
        )
        return info


class HomeMutations(graphene.ObjectType):
    """Contains all AxForm mutations"""
    create_form = CreateForm.Field()
    update_form = UpdateForm.Field()
    delete_form = DeleteForm.Field()
    create_folder = CreateFolder.Field()
    update_folder = UpdateFolder.Field()
    delete_folder = DeleteFolder.Field()
    change_forms_positions = ChangeFormsPositions.Field()
