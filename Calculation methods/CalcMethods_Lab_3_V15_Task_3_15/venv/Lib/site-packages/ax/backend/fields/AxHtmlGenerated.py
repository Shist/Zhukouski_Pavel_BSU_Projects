"""AxNum field type functions - before, after / insert, update, delete"""
import json
import backend.exec as ax_exec


async def before_display(db_session, field, form, current_user):
    """
    Executes python code from AxField.private_options

    Returns:
        Object: Returns updated value of current field"""
    del db_session
    if not field.private_options_json or field.private_options_json == '{}':
        return None

    try:
        options = json.loads(field.private_options_json)
        code = options['code']
        ax = await ax_exec.execute_field_code(
            code=code,
            form=form,
            current_user=current_user)
        field.value = ax.value
        return field.value
    except Exception as exc:
        return (f"There was error with executing AxHtml."
                f"Please check field options: {exc}")
