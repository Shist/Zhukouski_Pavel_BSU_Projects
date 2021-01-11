"""AxChangelog field type functions - before, after / insert, update, delete"""
import time


async def before_update(db_session, field, before_form, tobe_form, action,
                        current_user):
    """Python code runs for field before update

    Args:
        field (AxField): Current field. Is used for value and guid.
        before_form (AxForm): form with values of initial row.
        Used only for info. Modification is pointles.
        tobe_form (AxForm): form that will be used for database query.
        You can modify other fields here.
        action (AxAction): Performed action
        current_user (AxUser): Current user

    Returns:
        Object: Returns updated value of current field"""

    del db_session

    field_val = []
    changed_fields = []

    if field.value:
        field_val = field.value
        # json.loads(field.value)

    for f_before in before_form.fields:
        for f_after in tobe_form.fields:
            if f_before.db_name == f_after.db_name:
                if str(f_before.value) != str(f_after.value):
                    changed_field = {
                        "name": f_after.name,
                        "db_name": f_after.db_name,
                        "value": str(f_after.value)
                    }
                    changed_fields.append(changed_field)

    user = 'Anon'
    if current_user:
        user = current_user['email']

    log_obj = {
        "action": {
            "guid": str(action.guid),
            "name": action.name,
            "messages": action.messages
        },
        "changed_fields": changed_fields,
        "user": user,
        "timestamp": str(time.time())
    }
    field_val.append(log_obj)
    return field_val


async def before_insert(db_session, field, before_form, tobe_form, action,
                        current_user):
    """ before insert """
    del before_form, field, db_session

    field_val = []
    changed_fields = []

    for f_after in tobe_form.fields:
        if f_after.value:
            changed_field = {
                "name": f_after.name,
                "db_name": f_after.db_name,
                "value": str(f_after.value)
            }
            changed_fields.append(changed_field)

    user = 'Anon'
    if current_user:
        user = current_user['email']

    # TODO: add user info
    log_obj = {
        "action": {
            "guid": str(action.guid),
            "name": action.name,
            "messages": action.messages
        },
        "changed_fields": changed_fields,
        "user": user,
        "timestamp": str(time.time())
    }
    field_val.append(log_obj)
    return field_val
