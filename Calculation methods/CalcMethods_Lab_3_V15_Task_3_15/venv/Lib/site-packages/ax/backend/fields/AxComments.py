"""AxFiles field type functions - before, after / insert, update, delete"""
import os
import uuid
import shutil
import backend.misc as ax_misc
from backend.model import AxMessageThread, AxMessage


async def before_insert(db_session, field, before_form, tobe_form, action,
                        current_user):
    """ Create AxThread  """
    thread_guid = uuid.uuid4()
    new_thread = AxMessageThread()
    new_thread.guid = thread_guid
    new_thread.field_guid = field.guid
    new_thread.row_guid = tobe_form.row_guid
    db_session.add(new_thread)
    db_session.flush()

    field.needs_sql_update = True
    field.value = thread_guid
    return field.value


async def after_delete(db_session, field, before_form, tobe_form, action,
                       current_user):
    """ Delete related AxMessageThread. In cascade it deletes all related
        AxMessages """
    thread = db_session.query(AxMessageThread).filter(
        AxMessageThread.guid == uuid.UUID(field.value)
    ).first()
    if thread:
        db_session.query(AxMessage).filter(
            AxMessage.thread_guid == thread.guid
        ).delete()
        db_session.flush()

        db_session.delete(thread)
        db_session.commit()

    return field.value
