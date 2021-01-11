"""
AxNum field type functions - before, after / insert, update, delete

How to use in code:
    from datetime import datetime, timedelta
    expire = datetime.utcnow() + timedelta(days=366)
    ax.row.expire = expire.timestamp()

"""
import json


async def before_insert(db_session, field, before_form, tobe_form, action,
                        current_user):
    """
    Executes python code from AxField.private_options

    Returns:
        Object: Returns updated value of current field"""
    del before_form, action, db_session, tobe_form, current_user

    options = json.loads(field.options_json)
    default_now = options.get('defaultNow', None)
    if default_now:
        field.force_sql_update = True

    return field.value
