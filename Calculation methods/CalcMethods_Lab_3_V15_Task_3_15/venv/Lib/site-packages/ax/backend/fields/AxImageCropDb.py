"""AxImageCropDb field type functions - before, after / insert, update, delete
"""
import os
import shutil
import backend.misc as ax_misc


async def before_update(db_session, field, before_form, tobe_form, action,
                        current_user):
    """
    Reads file from tmp/<file_guid>/<file_name> and sets it as
    field value. It will be inserted to database
    Returns:
        Object: Returns updated value of current field"""
    del before_form, action, current_user, tobe_form, db_session
    file = field.value

    # value contaiins tmp file dict
    if file and 'guid' in file:
        tmp_folder = os.path.join(ax_misc.tmp_root_dir, file['guid'])
        tmp_path = os.path.join(tmp_folder, file['name'])
        with open(tmp_path, 'rb') as img:
            field.value = img.read()
        shutil.rmtree(tmp_folder)
    else:
        field.needs_sql_update = False

    return field.value


async def before_insert(db_session, field, before_form, tobe_form, action,
                        current_user):
    """ Do the same as after_update """
    return await before_update(
        db_session, field, before_form, tobe_form, action, current_user)
