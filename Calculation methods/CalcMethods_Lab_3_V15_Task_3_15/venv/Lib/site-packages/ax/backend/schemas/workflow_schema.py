""" This is part of GraphQL schema (Mutaions, Queryes, Subscriptions).
Workflow manipulation - create/update/delete - State, Action, Role,
Role2Action, Role2State, StatePermissions"""
import uuid
import graphene
# from loguru import logger
from backend.model import AxField, AxAction, AxState, \
    AxRole, AxRoleFieldPermission, AxState2Role, AxAction2Role, AxRole2Users
import backend.model as ax_model
from backend.schemas.types import State, Action, \
    State2Role, Action2Role, RoleFieldPermission, Role
from backend.auth import ax_admin_only
import backend.misc as ax_misc
import backend.auth as ax_auth


class CreateState(graphene.Mutation):
    """Create AxState

    Arguments:
        name (str): Name of created state. Usualy - default name from locale
        update (str): Default self-action name from locale. Like 'Update'
        form_guid (str): Guid of current AxForm
        x (float): X position of state in d3 workflow
        y (float): X position of state in d3 workflow

    Returns:
        state (AxState): Created state
        action (AxAction): Created update action
        permissions (List(AxRoleFieldPermission)): Default admin permissions
    """
    class Arguments:  # pylint: disable=missing-docstring
        name = graphene.String()
        update = graphene.String(required=False, default_value=None)
        form_guid = graphene.String()
        x = graphene.Float()
        y = graphene.Float()

    ok = graphene.Boolean()
    state = graphene.Field(State)
    action = graphene.Field(Action)
    permissions = graphene.List(RoleFieldPermission)

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = "workflow_schema -> CreateState"
        with ax_model.try_catch(info.context['session'], err) as db_session:
            ax_form_guid = uuid.UUID(args.get('form_guid'))

            new_state = AxState()
            new_state.name = args.get('name')
            new_state.form_guid = ax_form_guid
            new_state.x = args.get('x')
            new_state.y = args.get('y')

            db_session.add(new_state)
            db_session.flush()

            # Create default self-action
            update_action = None
            if args.get('update'):
                update_action = AxAction()
                update_action.name = args.get('update')
                update_action.form_guid = ax_form_guid
                update_action.from_state_guid = new_state.guid
                update_action.to_state_guid = new_state.guid
                db_session.add(update_action)

            return CreateState(
                state=new_state,
                action=update_action,
                permissions=[],
                ok=True)


class UpdateState(graphene.Mutation):
    """Update AxState"""
    class Arguments:  # pylint: disable=missing-docstring
        guid = graphene.String()
        name = graphene.String()
        x = graphene.Float()
        y = graphene.Float()

    ok = graphene.Boolean()
    state = graphene.Field(State)

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = "workflow_schema -> UpdateState"
        with ax_model.try_catch(info.context['session'], err) as db_session:
            ax_state = db_session.query(AxState).filter(
                AxState.guid == uuid.UUID(args.get('guid'))
            ).first()
            if args.get('name'):
                ax_state.name = args.get('name')
                await ax_auth.write_dynamic_roles_cache(db_session)
            if args.get('x'):
                ax_state.x = args.get('x')
            if args.get('y'):
                ax_state.y = args.get('y')
            return UpdateState(state=ax_state, ok=True)


class DeleteState(graphene.Mutation):
    """Deletes AxState"""
    class Arguments:  # pylint: disable=missing-docstring
        guid = graphene.String()

    ok = graphene.Boolean()
    deleted = graphene.String()

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = "workflow_schema -> DeleteState"
        with ax_model.try_catch(info.context['session'], err) as db_session:
            guid = args.get('guid')
            ax_state = db_session.query(AxState).filter(
                AxState.guid == uuid.UUID(guid)
            ).first()

            db_session.query(AxAction).filter(
                AxAction.from_state_guid == uuid.UUID(guid)
            ).delete()

            db_session.query(AxAction).filter(
                AxAction.to_state_guid == uuid.UUID(guid)
            ).delete()

            db_session.delete(ax_state)
            return DeleteState(deleted=guid, ok=True)


class CreateAction(graphene.Mutation):
    """Creates AxAction"""
    class Arguments:  # pylint: disable=missing-docstring
        form_guid = graphene.String()
        name = graphene.String()
        from_state_guid = graphene.String()
        to_state_guid = graphene.String()

    ok = graphene.Boolean()
    action = graphene.Field(Action)

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = "workflow_schema -> CreateAction"
        with ax_model.try_catch(info.context['session'], err) as db_session:
            new_action = AxAction()
            new_action.name = args.get('name')
            new_action.form_guid = args.get('form_guid')
            new_action.from_state_guid = args.get('from_state_guid')
            new_action.to_state_guid = args.get('to_state_guid')
            db_session.add(new_action)

            return CreateAction(action=new_action, ok=True)


class UpdateAction(graphene.Mutation):
    """Updates AxAction"""
    class Arguments:  # pylint: disable=missing-docstring
        guid = graphene.String()
        name = graphene.String(required=False, default_value=None)
        db_name = graphene.String(required=False, default_value=None)
        code = graphene.String(required=False, default_value=None)
        confirm_text = graphene.String(required=False, default_value=None)
        close_modal = graphene.Boolean(required=False, default_value=None)
        icon = graphene.String(required=False, default_value=None)
        radius = graphene.Float(required=False, default_value=None)

    ok = graphene.Boolean()
    action = graphene.Field(Action)

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = "workflow_schema -> UpdateAction"
        with ax_model.try_catch(info.context['session'], err) as db_session:
            ax_action = db_session.query(AxAction).filter(
                AxAction.guid == uuid.UUID(args.get('guid'))
            ).first()

            if args.get('name'):
                ax_action.name = args.get('name')
            if args.get('db_name'):
                ax_action.db_name = args.get('db_name')
            if args.get('code') is not None:
                if args.get('code') == '':
                    ax_action.code = None
                else:
                    ax_action.code = args.get('code')
            if args.get('confirm_text'):
                ax_action.confirm_text = args.get('confirm_text')
            if args.get('close_modal') is not None:
                ax_action.close_modal = args.get('close_modal')
            if args.get('icon'):
                ax_action.icon = args.get('icon')
            if args.get('radius') is not None:
                ax_action.radius = args.get('radius')

            return UpdateAction(action=ax_action, ok=True)


class DeleteAction(graphene.Mutation):
    """Deletes AxAction"""
    class Arguments:  # pylint: disable=missing-docstring
        guid = graphene.String()

    ok = graphene.Boolean()
    deleted = graphene.String()

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = "workflow_schema -> DeleteAction"
        with ax_model.try_catch(info.context['session'], err) as db_session:
            guid = args.get('guid')
            ax_action = db_session.query(AxAction).filter(
                AxAction.guid == uuid.UUID(guid)
            ).first()
            db_session.delete(ax_action)
            return DeleteAction(deleted=guid, ok=True)


def get_default_dynamic_role_code():
    """ Returns default code for dynamic role. """
    code = f"""ax.result = False
if(ax.row.some_field == ax.user_email):
    ax.result = True"""
    return code


class CreateRole(graphene.Mutation):
    """Creates AxRole"""
    class Arguments:  # pylint: disable=missing-docstring
        form_guid = graphene.String()
        name = graphene.String()
        is_dynamic = graphene.Boolean()

    ok = graphene.Boolean()
    role = graphene.Field(Role)

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = "workflow_schema -> CreateRole"
        with ax_model.try_catch(info.context['session'], err) as db_session:
            ax_role = AxRole()
            ax_role.name = args.get('name')
            ax_role.form_guid = args.get('form_guid')
            ax_role.is_dynamic = args.get('is_dynamic')
            if ax_role.is_dynamic:
                ax_role.icon = 'fas fa-user-cog'
                ax_role.code = get_default_dynamic_role_code()
            db_session.add(ax_role)
            return CreateRole(role=ax_role, ok=True)


class UpdateRole(graphene.Mutation):
    """Updates AxRole"""
    class Arguments:  # pylint: disable=missing-docstring
        guid = graphene.String()
        name = graphene.String(required=False, default_value=None)
        icon = graphene.String(required=False, default_value=None)
        code = graphene.String(required=False, default_value=None)

    ok = graphene.Boolean()
    role = graphene.Field(Role)

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = "workflow_schema -> UpdateRole"
        with ax_model.try_catch(info.context['session'], err) as db_session:
            ax_role = db_session.query(AxRole).filter(
                AxRole.guid == uuid.UUID(args.get('guid'))
            ).first()
            if args.get('name'):
                ax_role.name = args.get('name')
            if args.get('icon'):
                ax_role.icon = args.get('icon')
            if args.get('code'):
                ax_role.code = args.get('code')

            return UpdateRole(role=ax_role, ok=True)


class DeleteRole(graphene.Mutation):
    """Deletes AxRole"""
    class Arguments:  # pylint: disable=missing-docstring
        guid = graphene.String()

    ok = graphene.Boolean()
    deleted = graphene.String()

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = "workflow_schema -> DeleteRole"
        with ax_model.try_catch(info.context['session'], err) as db_session:
            guid = args.get('guid')

            db_session.query(AxRole2Users).filter(
                AxRole2Users.role_guid == uuid.UUID(guid)
            ).delete()

            db_session.query(AxState2Role).filter(
                AxState2Role.role_guid == uuid.UUID(guid)
            ).delete()

            db_session.query(AxAction2Role).filter(
                AxAction2Role.role_guid == uuid.UUID(guid)
            ).delete()

            db_session.query(AxRoleFieldPermission).filter(
                AxRoleFieldPermission.role_guid == uuid.UUID(guid)
            ).delete()

            ax_role = db_session.query(AxRole).filter(
                AxRole.guid == uuid.UUID(guid)
            ).first()

            db_session.delete(ax_role)
            return DeleteRole(deleted=guid, ok=True)


class AddRoleToState(graphene.Mutation):
    """Create AxState2Role"""
    class Arguments:  # pylint: disable=missing-docstring
        state_guid = graphene.String()
        role_guid = graphene.String()

    ok = graphene.Boolean()
    state2role = graphene.Field(State2Role)

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = "workflow_schema -> AddRoleToState"
        with ax_model.try_catch(info.context['session'], err) as db_session:
            role_guid = args.get('role_guid')
            state_guid = args.get('state_guid')
            existing_state2role = db_session.query(
                AxState2Role
            ).filter(
                AxState2Role.role_guid == uuid.UUID(role_guid)
            ).filter(
                AxState2Role.state_guid == uuid.UUID(state_guid)
            ).first()

            if existing_state2role:
                ok = True
                return AddRoleToState(state2role=existing_state2role, ok=ok)

            state2role = AxState2Role()
            state2role.state_guid = uuid.UUID(state_guid)
            state2role.role_guid = uuid.UUID(role_guid)

            db_session.add(state2role)
            return AddRoleToState(state2role=state2role, ok=True)


class DeleteRoleFromState(graphene.Mutation):
    """Deletes AxState2Role"""
    class Arguments:  # pylint: disable=missing-docstring
        guid = graphene.String()
        role_guid = graphene.String()
        state_guid = graphene.String()

    ok = graphene.Boolean()
    deleted = graphene.String()
    role_guid = graphene.String()
    state_guid = graphene.String()

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = "workflow_schema -> DeleteRoleFromState"
        with ax_model.try_catch(info.context['session'], err) as db_session:
            guid = args.get('guid')
            role_guid = args.get('role_guid')
            state_guid = args.get('state_guid')

            role2state = None
            if guid:
                role2state = db_session.query(AxState2Role).filter(
                    AxState2Role.guid == uuid.UUID(guid)
                ).first()
            else:
                role2state = db_session.query(AxState2Role).filter(
                    AxState2Role.role_guid == uuid.UUID(role_guid)
                ).filter(
                    AxState2Role.state_guid == uuid.UUID(state_guid)
                ).first()

            if role2state:
                the_role_guid = role2state.role_guid
                the_state_guid = role2state.state_guid

                db_session.delete(role2state)
                return DeleteRoleFromState(
                    deleted=guid,
                    role_guid=the_role_guid,
                    state_guid=the_state_guid,
                    ok=True)


class AddRoleToAction(graphene.Mutation):
    """Create AxAction2Role"""
    class Arguments:  # pylint: disable=missing-docstring
        action_guid = graphene.String()
        role_guid = graphene.String()

    ok = graphene.Boolean()
    action2role = graphene.Field(Action2Role)

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = "workflow_schema -> AddRoleToAction"
        with ax_model.try_catch(info.context['session'], err) as db_session:
            role_guid = args.get('role_guid')
            action_guid = args.get('action_guid')
            existing_action2role = db_session.query(
                AxAction2Role
            ).filter(
                AxAction2Role.role_guid == uuid.UUID(role_guid)
            ).filter(
                AxAction2Role.action_guid == uuid.UUID(action_guid)
            ).first()

            if existing_action2role:
                ok = True
                return AddRoleToAction(action2role=existing_action2role, ok=ok)

            action2role = AxAction2Role()
            action2role.action_guid = uuid.UUID(action_guid)
            action2role.role_guid = uuid.UUID(role_guid)

            db_session.add(action2role)
            return AddRoleToAction(action2role=action2role, ok=True)


class DeleteRoleFromAction(graphene.Mutation):
    """Deletes AxAction2Role"""
    class Arguments:  # pylint: disable=missing-docstring
        guid = graphene.String()
        action_guid = graphene.String()
        role_guid = graphene.String()

    ok = graphene.Boolean()
    deleted = graphene.String()
    role_guid = graphene.String()
    action_guid = graphene.String()

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = "workflow_schema -> DeleteRoleFromAction"
        with ax_model.try_catch(info.context['session'], err) as db_session:
            guid = args.get('guid')
            action_guid = args.get('action_guid')
            role_guid = args.get('role_guid')

            role2action = None
            if guid:
                role2action = db_session.query(AxAction2Role).filter(
                    AxAction2Role.guid == uuid.UUID(guid)
                ).first()
            else:
                role2action = db_session.query(AxAction2Role).filter(
                    AxAction2Role.role_guid == uuid.UUID(role_guid)
                ).filter(
                    AxAction2Role.action_guid == uuid.UUID(action_guid)
                ).first()

            deleted = role2action.guid
            db_session.delete(role2action)
            return DeleteRoleFromAction(
                deleted=deleted,
                ok=True,
                role_guid=role_guid,
                action_guid=action_guid)


class SetStatePermission(graphene.Mutation):
    """Creates AxRoleFieldPermission or multiple if tab field is presented"""
    class Arguments:  # pylint: disable=missing-docstring
        form_guid = graphene.String()
        state_guid = graphene.String()
        role_guid = graphene.String()
        field_guid = graphene.String(required=False, default_value=None)
        read = graphene.Boolean()
        edit = graphene.Boolean()

    ok = graphene.Boolean()
    permissions = graphene.List(RoleFieldPermission)

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = "workflow_schema -> SetStatePermission"
        with ax_model.try_catch(info.context['session'], err) as db_session:
            form_guid = args.get('form_guid')
            state_guid = args.get('state_guid')
            role_guid = args.get('role_guid')
            field_guid = args.get('field_guid')
            read = args.get('read')
            edit = args.get('edit')

            ax_field_guid = None
            ax_field = None
            if field_guid:
                ax_field = db_session.query(AxField).filter(
                    AxField.guid == uuid.UUID(field_guid)).first()
                ax_field_guid = ax_field.guid

            # If field_guid is null, then access is set for whole form
            # We must delete all fields permissions
            if not ax_field:
                db_session.query(
                    AxRoleFieldPermission
                ).filter(
                    AxRoleFieldPermission.state_guid == uuid.UUID(state_guid)
                ).filter(
                    AxRoleFieldPermission.role_guid == uuid.UUID(role_guid)
                ).delete()
            else:
                # if field or tab clicked - we must delete
                # permission fo all fields
                db_session.query(
                    AxRoleFieldPermission
                ).filter(
                    AxRoleFieldPermission.state_guid == uuid.UUID(state_guid)
                ).filter(
                    AxRoleFieldPermission.role_guid == uuid.UUID(role_guid)
                ).filter(
                    AxRoleFieldPermission.field_guid.is_(None)
                ).delete()

            # If field is tab - web must delete all permission for fields
            # of this tab
            if ax_field and ax_field.is_tab:
                tab_fields = db_session.query(AxField).filter(
                    AxField.parent == ax_field_guid
                ).all()
                tab_fields_guids = [fld.guid for fld in tab_fields]

                tab_perms = db_session.query(
                    AxRoleFieldPermission
                ).filter(
                    AxRoleFieldPermission.state_guid == uuid.UUID(state_guid)
                ).filter(
                    AxRoleFieldPermission.role_guid == uuid.UUID(role_guid)
                ).filter(
                    AxRoleFieldPermission.field_guid.in_(tab_fields_guids)
                ).all()

                for perm in tab_perms:
                    db_session.delete(perm)

            # If field is not tab - web must delete tab permission
            if ax_field and not ax_field.is_tab:
                db_session.query(
                    AxRoleFieldPermission
                ).filter(
                    AxRoleFieldPermission.state_guid == uuid.UUID(state_guid)
                ).filter(
                    AxRoleFieldPermission.role_guid == uuid.UUID(role_guid)
                ).filter(
                    AxRoleFieldPermission.field_guid == ax_field.parent
                ).delete()

            ax_perm = db_session.query(
                AxRoleFieldPermission
            ).filter(
                AxRoleFieldPermission.state_guid == uuid.UUID(state_guid)
            ).filter(
                AxRoleFieldPermission.role_guid == uuid.UUID(role_guid)
            ).filter(
                AxRoleFieldPermission.field_guid == ax_field_guid
            ).first()

            if ax_perm is None:
                ax_perm = AxRoleFieldPermission()
                ax_perm.form_guid = uuid.UUID(form_guid)
                ax_perm.role_guid = uuid.UUID(role_guid)
                ax_perm.field_guid = ax_field_guid
                ax_perm.state_guid = uuid.UUID(state_guid)
                ax_perm.read = read
                ax_perm.edit = edit
                db_session.add(ax_perm)
            else:
                ax_perm.read = read
                ax_perm.edit = edit

            db_session.flush()

            return_permissions = db_session.query(
                AxRoleFieldPermission
            ).filter(
                AxRoleFieldPermission.state_guid == uuid.UUID(state_guid)
            ).all()

            return SetStatePermission(permissions=return_permissions, ok=True)


class WorkflowQuery(graphene.ObjectType):
    """Workflow query"""
    ax_role = graphene.Field(
        Role,
        guid=graphene.Argument(type=graphene.String, required=True),
        update_time=graphene.Argument(type=graphene.String, required=False)
    )

    @ax_admin_only
    async def resolve_ax_role(self, info, guid, update_time=None):
        """Get AxRole with code"""
        del update_time
        err = 'Error in GQL query - resolve_ax_role.'
        with ax_model.try_catch(info.context['session'], err, no_commit=True):
            query = Role.get_query(info)  # SQLAlchemy query
            role_guid = ax_misc.guid_or_none(guid)
            ret_role = query.filter(
                AxRole.guid == role_guid
            ).first()
            return ret_role


class WorkflowMutations(graphene.ObjectType):
    """Combine all mutations"""
    create_state = CreateState.Field()
    update_state = UpdateState.Field()
    delete_state = DeleteState.Field()
    create_action = CreateAction.Field()
    update_action = UpdateAction.Field()
    delete_action = DeleteAction.Field()
    create_role = CreateRole.Field()
    update_role = UpdateRole.Field()
    delete_role = DeleteRole.Field()
    add_role_to_state = AddRoleToState.Field()
    delete_role_from_state = DeleteRoleFromState.Field()
    add_role_to_action = AddRoleToAction.Field()
    delete_role_from_action = DeleteRoleFromAction.Field()
    set_state_permission = SetStatePermission.Field()
