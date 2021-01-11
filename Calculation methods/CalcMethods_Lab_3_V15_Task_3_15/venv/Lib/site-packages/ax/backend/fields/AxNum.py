"""AxNum field type functions - before, after / insert, update, delete"""
import json
from backend.model import AxMetric
import backend.exec as ax_exec


async def before_insert(db_session, field, before_form, tobe_form, action,
                        current_user):
    """
    Executes python code from AxField.private_options

    Returns:
        Object: Returns updated value of current field"""
    del before_form, action

    if not field.private_options_json or field.private_options_json == '{}':
        return None

    # get current counter from AxMetric for current key
    # if there is none -> create one

    options = json.loads(field.private_options_json)
    code = options['algorithm']
    key = options['counterKey']

    if not key:
        return None

    current_counter = db_session.query(AxMetric).filter(
        AxMetric.key == key
    ).first()

    current_value = None
    if current_counter:
        current_value = current_counter.value
    else:
        current_counter = AxMetric()
        current_counter.key = key
        current_counter.value = None
        db_session.add(current_counter)

    arguments = {
        "counter": current_value
    }

    ax = await ax_exec.execute_field_code(
        code=code,
        form=tobe_form,
        arguments=arguments,
        current_user=current_user)

    field.needs_sql_update = True
    field.value = ax.value
    current_counter.value = ax.counter

    return field.value
