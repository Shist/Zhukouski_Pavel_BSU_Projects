""" Auth module based on sanic-jwt """

import os
import sys
import uuid
import functools
import datetime
import asyncio
from loguru import logger
from passlib.hash import pbkdf2_sha256
from sanic_jwt import exceptions, initialize, Configuration
from sanic_jwt.decorators import _do_protection

from backend.model import AxUser, AxGroup2Users, AxRole, AxRole2Users, \
    AxRoleFieldPermission, AxForm, AxAction2Role, AxField
import backend.cache as ax_cache
import backend.model as ax_model
import backend.misc as ax_misc
import backend.dialects as ax_dialects
import backend.exec as ax_exec
import backend.fields.AxAuthor as AxFieldAxAuthor  # pylint: disable=unused-import

this = sys.modules[__name__]


async def get_state_guid(ax_form, state_name):
    """ Returns guid of state by name.
        If no state_name provided -> returns guid of Start state """
    state_guid = None
    for state in ax_form.states:
        if state_name and state.name == state_name:
            state_guid = str(state.guid)
        elif ((state_name is None or state_name == '') and
              state.is_start is True):
            state_guid = str(state.guid)

    return state_guid


async def check_if_action_avalible(
        action,
        current_user,
        dynamic_role_guids=None):
    """ Checks action workflow perms and dynamic roles perms"""
    user_is_admin = current_user.get(
        'is_admin', False) if current_user else False
    user_guid = current_user.get('user_id', None) if current_user else None

    action_guid = str(action.guid)
    avalible = await check_action_perm(
        user_guid=user_guid, action_guid=action_guid)

    if dynamic_role_guids:
        for role_guid in dynamic_role_guids:
            if not avalible:
                avalible = await check_action_perm(
                    user_guid=role_guid, action_guid=action_guid)

    if avalible or user_is_admin:
        return True
    return False


async def check_action_perm(user_guid, action_guid):
    """ Checks for action_perm_ cache record. """
    user_guid_str = str(user_guid)
    action_guid_str = str(action_guid)
    action_key = f"action_perm_{user_guid_str}_{action_guid_str}"
    perm = await ax_cache.cache.get(action_key)
    return perm


async def get_allowed_fields_dict(ax_form, user_guid, state_guid):
    """ Gets allowed fields for user for specific state
         -> dict['field_guid'] = 1/2  ; 1 - read, 2 - edit"""
    cache_keys = []
    field_guids = []
    allowed_fields_dict = {}
    for field in ax_form.fields:
        user_guid = str(user_guid)
        field_guid = str(field.guid)
        state_guid = str(state_guid)
        key = f"perm_{user_guid}_{field_guid}_{state_guid}"
        cache_keys.append(key)
        field_guids.append(str(field.guid))

    cache_results = await ax_cache.cache.multi_get(cache_keys)

    for idx, field_guid in enumerate(field_guids):
        perm_value = cache_results[idx]
        allowed_fields_dict[field_guid] = perm_value

    return allowed_fields_dict


async def check_field_perm(db_session, current_user, field_guid, row_guid):
    """ Checks if user can view or modify for specific field and row
        returns None = forbidden, 1 = read, 2 = edit"""

    user_guid = current_user.get("user_id", None) if current_user else None
    user_id_admin = current_user.get(
        "is_admin", False) if current_user else False

    if user_id_admin:
        return 2

    ax_field = db_session.query(AxField).filter(
        AxField.guid == uuid.UUID(str(field_guid))
    ).first()

    result = await ax_dialects.dialect.select_one(
        db_session=db_session,
        form=ax_field.form,
        fields_list=[],
        row_guid=row_guid)

    state_name = result[0]['axState']
    state_guid = await get_state_guid(
        ax_form=ax_field.form, state_name=state_name)
    key = f"perm_{user_guid}_{ax_field.guid}_{state_guid}"
    perm = await ax_cache.cache.get(key)
    return perm


async def get_grid_allowed_fields_dict(ax_form, user_guid):
    """ Gets allowed fields for user for all states
            -> dict['state_name']['field_db_name'] = 1/2 """
    cache_keys = []
    for state in ax_form.states:
        for field in ax_form.no_tab_fields:
            user_guid = str(user_guid)
            field_guid = str(field.guid)
            state_guid = str(state.guid)
            key = f"perm_{user_guid}_{field_guid}_{state_guid}"
            cache_keys.append(key)

    cache_results = await ax_cache.cache.multi_get(cache_keys)

    allowed_fields_dict = {}
    idx = 0
    for state in ax_form.states:
        allowed_fields_dict[state.name] = {}
        for field in ax_form.no_tab_fields:
            field_db_name = field.db_name
            if field.is_virtual:
                field_db_name = field.field_type.virtual_source
            allowed_fields_dict[state.name][field_db_name] = cache_results[idx]
            idx += 1
    return allowed_fields_dict


async def get_dynamic_roles_guids(ax_form, current_user):
    """ Get list of role guids of all dynamic roles of form.
        For each dynamic role - check if form values and user fits role """
    role_guids = []
    for role in ax_form.roles:
        if role.is_dynamic:
            # check if user and form fits dynamic role.
            form_fits_role = await check_fits_dynamic_role(
                role=role,
                ax_form=ax_form,
                current_user=current_user)
            if form_fits_role is True:
                role_guids.append(str(role.guid))
    return role_guids


async def check_fits_dynamic_role(role, ax_form, current_user):
    """ Runs check_dynamic_role() of field_type py file """
    if role.is_dynamic:
        fits = await ax_exec.execute_field_code(
            code=role.code,
            form=ax_form,
            current_user=current_user)
        if 'result' in fits and fits['result'] is True:
            return True
    return False


async def set_form_visibility(
        ax_form,
        state_guid,
        current_user,
        dynamic_role_guids=None):
    """ Sets permission field visibility. Deletes value if field is hidden """
    user_guid = current_user.get("user_id", None) if current_user else None
    user_id_admin = current_user.get(
        "is_admin", False) if current_user else False
    allowed_fields = await get_allowed_fields_dict(
        ax_form=ax_form,
        user_guid=user_guid,
        state_guid=state_guid)

    # Apply worklfow perms
    for field in ax_form.no_tab_fields:
        if field in ax_form.db_fields or field.field_type.is_virtual:
            field_guid_str = str(field.guid)
            field.is_hidden = True
            if user_id_admin:
                field.is_readonly = False
                field.is_hidden = False
            else:
                if field_guid_str in allowed_fields:
                    if allowed_fields[field_guid_str] == 1:
                        field.is_readonly = True
                        field.is_hidden = False
                    if allowed_fields[field_guid_str] == 2:
                        field.is_readonly = False
                        field.is_hidden = False

    # Apply dynamic role perms (rewrite previos perms)
    if dynamic_role_guids:
        for role_guid in dynamic_role_guids:
            allowed_role_fields = await get_allowed_fields_dict(
                ax_form=ax_form,
                user_guid=role_guid,
                state_guid=state_guid)

            for field in ax_form.no_tab_fields:
                if field in ax_form.db_fields or field.field_type.is_virtual:
                    field_guid_str = str(field.guid)
                    if field_guid_str in allowed_role_fields:
                        if allowed_role_fields[field_guid_str] == 1:
                            field.is_readonly = True
                            field.is_hidden = False
                        if allowed_role_fields[field_guid_str] == 2:
                            field.is_readonly = False
                            field.is_hidden = False
                            field.needs_sql_update = True

    for field in ax_form.db_fields:
        if not field.field_type.is_updated_always:
            # If field is hidden -> Epty the value and forbid
            # inser and update
            if field.is_hidden is True:
                field.value = None
                field.needs_sql_update = False

            # Forbid update if readonly
            if field.is_readonly is True:
                field.needs_sql_update = False

    return ax_form


async def check_if_admin(user_guid, db_session):
    """ Checks if user is adimn and writes  <user_is_admin_{user_guid}> cache"""
    err = "Error -> Auth -> check_if_admin"
    with ax_model.try_catch(db_session, err):
        # Get admin group, check if
        admin_group = db_session.query(AxUser).filter(
            AxUser.is_admin.is_(True)
        ).filter(
            AxUser.is_group.is_(True)
        ).first()

        group2user = db_session.query(AxGroup2Users).filter(
            AxGroup2Users.group_guid == admin_group.guid
        ).filter(
            AxGroup2Users.user_guid == uuid.UUID(user_guid)
        ).first()

        if group2user:
            key = f'user_is_admin_{user_guid}'
            await ax_cache.cache.set(key, True)


async def write_perm_cache(db_session, user_guid):
    """ On each user token refresh we write to cache permissions for
        each field/state combination """
    perm_cache_pairs = []
    # debug_list = []
    user_and_groups = []

    # Add 'everyone' group
    everyone_group = db_session.query(AxUser).filter(
        AxUser.is_everyone.is_(True)
    ).first()
    if everyone_group:
        user_and_groups.append(everyone_group.guid)

    if user_guid:
        # Add current user
        user_and_groups.append(uuid.UUID(user_guid))

        # Add all-users group
        # TODO get this from cache!
        all_users_group = db_session.query(AxUser).filter(
            AxUser.is_all_users.is_(True)
        ).first()
        user_and_groups.append(all_users_group.guid)

        # Get user groups
        group2user_result = db_session.query(AxGroup2Users).filter(
            AxGroup2Users.user_guid == uuid.UUID(user_guid)
        ).all()
        for g2u in group2user_result:
            if g2u.group_guid not in user_and_groups:
                user_and_groups.append(g2u.group_guid)

    # Get roles of user and his groups
    roles_guids = []
    role2user_result = db_session.query(AxRole2Users).filter(
        AxRole2Users.user_guid.in_(user_and_groups)
    ).all()
    for r2u in role2user_result:
        if r2u.role_guid not in roles_guids:
            roles_guids.append(r2u.role_guid)

    # Get AxRoleFieldPermission for those roles
    forms_guids = []
    perms = db_session.query(AxRoleFieldPermission).filter(
        AxRoleFieldPermission.role_guid.in_(roles_guids)
    ).all()
    for perm in perms:
        if perm.form_guid not in forms_guids:
            forms_guids.append(perm.form_guid)

    # Get AxAction2Role for those roles
    actions_guids = []
    action_role_result = db_session.query(AxAction2Role).filter(
        AxAction2Role.role_guid.in_(roles_guids)
    ).all()
    for a2r in action_role_result:
        if a2r.action_guid not in actions_guids:
            actions_guids.append(a2r.action_guid)
            action_guid = str(a2r.action_guid)
            action_key = f"action_perm_{user_guid}_{action_guid}"
            perm_cache_pairs.append([action_key, True])

    # Get all forms with perms
    all_forms = db_session.query(AxForm).filter(
        AxForm.guid.in_(forms_guids)
    ).all()

    # For each form
    for ax_form in all_forms:
        # For each field
        for ax_field in ax_form.no_tab_fields:
            # For each state
            for ax_state in ax_form.perm_states:
                read = False
                edit = False
                # For each perm
                form_perms = [p for p in perms if (
                    p.form_guid == ax_form.guid and
                    p.state_guid == ax_state.guid)]
                for perm in form_perms:
                    # if perm is set to whole form
                    # if perm is set to tab
                    # if perm is set to field

                    if (perm.field_guid is None or
                            perm.field_guid == ax_field.parent or
                            perm.field_guid == ax_field.guid):

                        if perm.read is True:
                            read = True
                        if perm.edit is True:
                            edit = True

                # Write cache perm_<user_guid>_<field_guid>_<state_guid> = 0/1/2
                field_guid = str(ax_field.guid)
                state_guid = str(ax_state.guid)
                key = f"perm_{user_guid}_{field_guid}_{state_guid}"
                value = 0
                if read is True:
                    value = 1
                if edit is True:
                    value = 2

                perm_cache_pairs.append([key, value])
                # debug_list.append(
                #     (f"{ax_form.db_name} -> "
                #      f"{ax_state.name} -> {ax_field.db_name} -> {value}")
                # )

    expire_seconds = 60 * 20  # 20 mins #TODO check this timeout
    if user_guid is None:
        expire_seconds = 0  # disable ttl for Everyone group
    await ax_cache.cache.multi_set(perm_cache_pairs, ttl=expire_seconds)


async def write_dynamic_roles_cache(db_session):
    """ Write cache for each field/state combination
        perm_{dynamic_role_guid}_{field_guid}_{state_guid}
        Write cache needed on start and after each perm edit, if role is dynamic
        """
    perm_cache_pairs = []
    debug_list = []

    # Get all dynamic roles
    roles_guids = []
    dynamic_roles = db_session.query(AxRole).filter(
        AxRole.is_dynamic.is_(True)
    ).all()
    for role in dynamic_roles:
        roles_guids.append(role.guid)

    # Get AxRoleFieldPermission for those roles
    forms_guids = []
    perms = db_session.query(AxRoleFieldPermission).filter(
        AxRoleFieldPermission.role_guid.in_(roles_guids)
    ).all()
    for perm in perms:
        if perm.form_guid not in forms_guids:
            forms_guids.append(perm.form_guid)

    # Get AxAction2Role for those roles
    action_role_result = db_session.query(AxAction2Role).filter(
        AxAction2Role.role_guid.in_(roles_guids)
    ).all()
    actions_guids = []
    for a2r in action_role_result:
        if a2r.action_guid not in actions_guids:
            actions_guids.append(a2r.action_guid)
            action_guid = str(a2r.action_guid)
            role_guid = str(a2r.role_guid)
            action_key = f"action_perm_{role_guid}_{action_guid}"
            perm_cache_pairs.append([action_key, True])

    # Get all forms with perms
    all_forms = db_session.query(AxForm).filter(
        AxForm.guid.in_(forms_guids)
    ).all()

    # For each form
    for ax_form in all_forms:
        # For each field
        for ax_field in ax_form.no_tab_fields:
            # For each state
            for ax_state in ax_form.perm_states:
                read = False
                edit = False
                # For each dynamic role
                for dyn_role in dynamic_roles:
                    role_perms = [p for p in perms if (
                        p.role_guid == dyn_role.guid and
                        p.state_guid == ax_state.guid)]

                    for perm in role_perms:
                        # if perm is set to whole form
                        # if perm is set to tab
                        # if perm is set to field
                        if (perm.field_guid is None or
                                perm.field_guid == ax_field.parent or
                                perm.field_guid == ax_field.guid):

                            if perm.read is True:
                                read = True
                            if perm.edit is True:
                                edit = True

                    # Cache perm_<role_guid>_<field_guid>_<state_guid> = 0/1/2
                    role_guid = str(dyn_role.guid)
                    field_guid = str(ax_field.guid)
                    state_guid = str(ax_state.guid)
                    key = f"perm_{role_guid}_{field_guid}_{state_guid}"
                    value = 0
                    if read is True:
                        value = 1
                    if edit is True:
                        value = 2

                    perm_cache_pairs.append([key, value])
                    debug_list.append(
                        (f"{dyn_role.name} -> {ax_form.db_name} -> "
                         f"{ax_state.name} -> {ax_field.db_name} -> {value}"))

    expire_seconds = 0  # does not depricate
    await ax_cache.cache.multi_set(perm_cache_pairs, ttl=expire_seconds)


async def write_info_cache(user):
    """ Save short_name and email in cache """
    name_key = f'user_short_name_{user.guid}'
    await ax_cache.cache.set(name_key, user.short_name)
    email_key = f'user_email_{user.guid}'
    await ax_cache.cache.set(email_key, user.email)


async def authenticate(request, *args, **kwargs):
    """ - """
    del args, kwargs
    msg = "Error -> Auth -> authenticate"
    with ax_model.scoped_session(msg) as db_session:
        email = request.json.get("email", None)
        password = request.json.get("password", None)

        if not email or not password:
            raise exceptions.AuthenticationFailed("Missing email or password.")

        user = db_session.query(AxUser).filter(
            AxUser.email == email
        ).filter(
            AxUser.is_blocked.is_(False)
        ).first()

        if user is None:
            raise exceptions.AuthenticationFailed("User not found.")

        if not pbkdf2_sha256.verify(password, user.password):
            raise exceptions.AuthenticationFailed("Password is incorrect.")

        await check_if_admin(user_guid=str(user.guid), db_session=db_session)
        await write_perm_cache(db_session=db_session, user_guid=str(user.guid))
        await write_info_cache(user)

        db_session.expunge(user)
        return user


def ax_protected(initialized_on=None, **kw):
    """ Wrapper for @protected sanic_jwt decorator.
    If not authorisation token is present - then it is anon user, do not send
    401 error  """
    def _aux(view):
        @functools.wraps(view)
        async def _inner(request, *args, **kwargs):
            # If there is no jwt headers -> then this is everyone user.
            # We must not protect route
            if 'authorization' not in request.headers:
                return await view(request, *args, **kwargs)
            if not "Bearer" in request.headers['authorization']:
                return await view(request, *args, **kwargs)

            kwargs.update({
                'initialized_on': initialized_on,
                'kw': kw,
                'request': request,
                'f': view,
            })
            return await _do_protection(*args, **kwargs)
        return _inner
    return _aux


def ax_admin_only(func):
    """ Decorator to check if user is admin """
    async def check_admin(*args, **kwargs):
        user = args[1].context["user"]
        if user and user["is_admin"] is True:
            return await func(*args, **kwargs)
        else:
            logger.error('Only for admins error')
            raise Exception('Only for admins')
    return check_admin


async def retrieve_user(request, payload, *args, **kwargs):
    """ Get user info. This info is transfered into routes with inject_user """
    del request, args, kwargs
    if payload:
        user_id = payload.get('user_id') or None

        if not ax_misc.string_is_guid(user_id):
            return None

        email = await ax_cache.cache.get(f'user_email_{user_id}')

        if not email:
            msg = "Auth -> retrieve_user"
            with ax_model.scoped_session(msg) as db_session:
                user = db_session.query(AxUser).filter(
                    AxUser.guid == ax_misc.guid_or_none(user_id)
                ).first()

                if user is not None:
                    # raise exceptions.AuthenticationFailed("User not found.")
                    await check_if_admin(
                        user_guid=user_id, db_session=db_session)
                    await write_perm_cache(
                        db_session=db_session, user_guid=user_id)
                    await write_info_cache(user)

        email = await ax_cache.cache.get(f'user_email_{user_id}')
        short_name = await ax_cache.cache.get(f'user_short_name_{user_id}')
        is_admin = await ax_cache.cache.get(f'user_is_admin_{user_id}')

        user = {
            "user_id": str(user_id),
            "is_admin": is_admin,
            "short_name": short_name,
            "email": email
        }
        return user
    else:
        return None


async def store_refresh_token(request, user_id, refresh_token, *args, **kwargs):
    """ Store refresh token in cache and write all perms cache for user """
    del args, kwargs
    device_guid = request.json['deviceGuid']
    key = f'refresh_token_{device_guid}_{user_id}'
    await ax_cache.cache.set(key, refresh_token)


async def retrieve_refresh_token(request, user_id, *args, **kwargs):
    """ Get refresh token from cache and refresh all perms cache for user """
    del args, kwargs
    device_guid = request.json['deviceGuid']
    key = f'refresh_token_{device_guid}_{user_id}'
    refresh_token = await ax_cache.cache.get(key)

    if refresh_token:
        with ax_model.scoped_session("Auth.store_refresh_token") as db_session:
            await check_if_admin(user_guid=user_id, db_session=db_session)
            await write_perm_cache(db_session=db_session, user_guid=user_id)

    return refresh_token


class AxConfiguration(Configuration):
    """ sanic-jwt config class """
    url_prefix = '/api/auth'


client_guid = None
user_num = None
expire_date = None


def apply_lise(db_session):
    """
        Copyright (C) 2020 Mikhail Marenov - All Rights Reserved
        You MAY NOT CHANGE source code of Ax workflow without writen permission
        author. If you change source code in order to activate PRO features -
        YOU MAY BE SUBJECT TO HEAVY CIVIL PENALTIES. THESE INCLUDE MONETARY
        DAMAGES, COURT COSTS, AND ATTORNEYS FEES INCURRED
        Please read LICENSE.md for more information.
    """
    import rsa
    import base64

    license_text = os.environ.get('AX_LICENSE', None)

    if license_text:
        public_key_str = (
            f'-----BEGIN RSA PUBLIC KEY-----\nMEgCQQCKDk8gSjXCh9R8VFKUMFhLxqx/'
            f'mkWDIUd9uMrHsbYs89t5GnMCoNkmL9nj\nazDQ2nyRxnVaYgJ2hFM49EomRFGVAg'
            f'MBAAE=\n-----END RSA PUBLIC KEY-----\n')
        public_key = rsa.PublicKey.load_pkcs1(public_key_str, 'PEM')
        data, signature = license_text.split('##')
        cl_guid, expire_str, users_number = data.split('#')
        expire = datetime.datetime.fromtimestamp(int(expire_str))
        sign = base64.b64decode(signature)

        time_delta = expire - datetime.datetime.utcnow()
        if time_delta.days <= 0:
            err = "License is expired!"
            logger.exception(err)
            raise Exception(err)

        try:
            rsa.verify(data.encode('utf-8'), sign, public_key)
        except rsa.VerificationError:
            logger.exception("License is not verified!")
            raise

        logger.info(f'License applied for {users_number} users.')
        this.client_guid = cl_guid
        this.user_num = int(users_number)
        this.expire = expire
    else:
        this.client_guid = None
        this.user_num = 5000
        this.expire = None

    number_of_users = db_session.query(AxUser).filter(
        AxUser.is_group.is_(False)
    ).filter(
        AxUser.is_blocked.is_(False)
    ).count()
    if number_of_users > this.user_num:
        err = f"Maximum number of users exceeded! Max={this.user_num}"
        logger.exception(err)
        raise Exception(err)


def lise_is_active():
    """
        Copyright (C) 2020 Mikhail Marenov - All Rights Reserved
        You MAY NOT CHANGE source code of Ax workflow without writen permission
        author. If you change source code in order to activate PRO features -
        YOU MAY BE SUBJECT TO HEAVY CIVIL PENALTIES. THESE INCLUDE MONETARY
        DAMAGES, COURT COSTS, AND ATTORNEYS FEES INCURRED
        Please read LICENSE.md for more information.
    """
    if this.client_guid:
        time_delta = this.expire - datetime.datetime.utcnow()
        if time_delta.days <= 0:
            err = "License is expired!"
            logger.exception(err)
            raise Exception(err)
        return True
    return False


def init_auth(sanic_app, secret="This is big secret, set me in app.yaml"):
    """
    Initiate sanic-jwt module

    Copyright (C) 2020 Mikhail Marenov - All Rights Reserved
    You MAY NOT CHANGE source code of Ax workflow without writen permission
    author. If you change source code in order to activate PRO features -
    YOU MAY BE SUBJECT TO HEAVY CIVIL PENALTIES. THESE INCLUDE MONETARY
    DAMAGES, COURT COSTS, AND ATTORNEYS FEES INCURRED
    Please read LICENSE.md for more information.
    """

    delta = 60  # seconds
    initialize(sanic_app,
               authenticate=authenticate,
               configuration_class=AxConfiguration,
               refresh_token_enabled=True,
               store_refresh_token=store_refresh_token,
               retrieve_refresh_token=retrieve_refresh_token,
               retrieve_user=retrieve_user,
               expiration_delta=delta,
               cookie_access_token_name='ax_auth',
               cookie_set=True,
               cookie_strict=False,
               login_redirect_url='/signin',
               secret=secret)

    with ax_model.scoped_session("init_auth - ERROR") as db_session:
        apply_lise(db_session)

        # Write cache form Everyone group
        asyncio.get_event_loop().run_until_complete(write_perm_cache(
            db_session=db_session, user_guid=None))

        # Write cache for dynamic roles
        asyncio.get_event_loop().run_until_complete(write_dynamic_roles_cache(
            db_session=db_session))
