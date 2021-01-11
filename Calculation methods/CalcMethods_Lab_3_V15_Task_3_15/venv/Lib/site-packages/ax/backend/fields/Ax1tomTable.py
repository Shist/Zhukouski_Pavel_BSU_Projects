"""Ax1tomTable field type functions - before, after / insert, update, delete"""
import uuid
import json
from backend.model import Ax1tomReference


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

    Sample SQL query:
        SELECT cars.guid, cars.model, cars.price, ref.child_guid, Countrey.name
        FROM Cars
        LEFT JOIN _ax_mtom_references as ref ON Cars.guid = ref.row_guid
        LEFT JOIN Countrey ON Countrey.guid = ref.child_guid;

    Returns:
        Object: Returns updated value of current field"""
    del before_form, action, current_user

    db_session.query(Ax1tomReference).filter(
        Ax1tomReference.field_guid == field.guid
    ).filter(
        Ax1tomReference.row_guid == uuid.UUID(str(tobe_form.row_guid))
    ).delete()

    if field.value:
        if not isinstance(field.value, list):
            field.value = json.loads(field.value)

        for child_guid in field.value:
            new_tom = Ax1tomReference()
            new_tom.form_guid = tobe_form.guid
            new_tom.field_guid = field.guid
            new_tom.row_guid = uuid.UUID(str(tobe_form.row_guid))
            new_tom.child_guid = uuid.UUID(str(child_guid))
            db_session.add(new_tom)

    return field.value
