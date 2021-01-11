"""AxAuthor
Before insert - write current user.
Before update - ignore change
after field is created - create dynamic role
before field is deleted - delete dynamic role


FORM
    get list of dynamic roles that user fits
    get allowed dict from cache
        normal - perm_{user_guid}_{field_guid}_{state_guid}
        dynamic - perm_{dynamic_role_guid}_{field_guid}_{state_guid}
                - action_perm_{dynamic_role_guid}_{action_guid}

GRID
    grid is same as roles on Start


"""
# import backend.model as ax_model
# from backend.model import AxRole


async def before_insert(db_session, field, before_form, tobe_form, action,
                        current_user):
    """ Create default value of field.  """
    del db_session, before_form, tobe_form, action
    field.value = None
    if current_user:
        field.value = current_user["email"]
    return field.value


async def before_update(db_session, field, before_form, tobe_form, action,
                        current_user):
    """ Create default value of field.  """
    del db_session, before_form, tobe_form, action, current_user
    field.needs_sql_update = False
    return field.value


# async def after_field_create(db_session, field, before_form, tobe_form, action,
#                              current_user):
#     """ Create Author role for current form """
#     err = "AxAuthor -> after_create"
#     with ax_model.try_catch(db_session, err) as db_session:

#         # Check if form already contains Author role
#         for role in tobe_form.roles:
#             if role.field_tag == "AxAuthor":
#                 return False

#         ax_role = AxRole()
#         ax_role.name = "Author"  # TODO ADD python locale!
#         ax_role.form_guid = tobe_form.guid
#         ax_role.icon = "fas fa-user-tag"
#         ax_role.field_tag = "AxAuthor"
#         db_session.add(ax_role)
#         return True


# async def before_field_delete(db_session, field, before_form, tobe_form, action,
#                               current_user):
#     """ If field is removed - Delete Author role for current form """
#     # check if form contains more then one
#     author_fields_count = 0
#     for fld in tobe_form.fields:
#         if fld.field_type_tag == "AxAuthor":
#             author_fields_count += 1

#     if author_fields_count == 1:
#         db_session.query(AxRole).filter(
#             AxRole.form_guid == tobe_form.guid
#         ).filter(
#             AxRole.field_tag == "AxAuthor"
#         ).delete()


async def check_dynamic_role(db_session, ax_form, current_user):
    """ Checks if form values and current user fits current dynamic role
    If Author field == current_user_email -> return True """
    del db_session
    for field in ax_form.fields:
        if field.field_type_tag == "AxAuthor":
            if field.value == current_user['email']:
                return True
    return False
