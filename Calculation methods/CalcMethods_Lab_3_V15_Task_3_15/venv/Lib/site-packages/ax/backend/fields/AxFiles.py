"""AxFiles field type functions - before, after / insert, update, delete"""
import os
import uuid
import shutil
import backend.misc as ax_misc


async def before_update(db_session, field, before_form, tobe_form, action,
                        current_user):
    """ Set isTmp of file to False. So file_view route will work with /uploads,
        not /tmp forlder """
    del db_session, before_form, tobe_form, action, current_user
    if field.value:
        for file in field.value:
            if file['isTmp']:
                file['isTmp'] = False
    return field.value


async def after_update(db_session, field, before_form, tobe_form, action,
                       current_user):
    """
    Moves uploaded files from /tmp/<file_guid>/<file_name> folder to
    /uploads/form_row_field_file/<form_guid>/<row_guid>/<file_guid>/<file_name>
    Returns:
        Object: Returns updated value of current field"""
    del before_form, action, current_user, db_session
    value_guids = []
    form_guid = str(tobe_form.guid)
    row_guid = str(uuid.UUID(str(tobe_form.row_guid)))
    field_guid = str(field.guid)

    if field.value and field.needs_sql_update:
        for file in field.value:
            value_guids.append(file['guid'])
            tmp_folder = os.path.join(ax_misc.tmp_root_dir, file['guid'])
            tmp_path = os.path.join(tmp_folder, file['name'])
            dist_folder = os.path.join(
                ax_misc.uploads_root_dir,
                'form_row_field_file',
                form_guid,
                row_guid,
                field_guid,
                file['guid'])
            dist_path = os.path.join(dist_folder, file['name'])

            # if file exists in tmp - move it to row folder
            if os.path.lexists(tmp_path) is True:
                if os.path.exists(dist_folder) is False:
                    os.makedirs(dist_folder)
                shutil.move(tmp_path, dist_path)
                shutil.rmtree(tmp_folder)

    # if form.row.field directory contains sub dirs with guid wich is not
    # in current value -> then file was deleted from field data,
    # We must delete this file from filesystem
    if field.needs_sql_update:
        field_folder = os.path.join(
            ax_misc.uploads_root_dir,
            'form_row_field_file',
            form_guid,
            row_guid,
            field_guid
        )
        if os.path.exists(field_folder) is True:
            for root, dirs, _ in os.walk(field_folder):
                del root
                for dir_name in dirs:
                    if dir_name not in value_guids:
                        dir_to_delete = os.path.join(field_folder, dir_name)
                        shutil.rmtree(dir_to_delete)

    return field.value


async def before_insert(db_session, field, before_form, tobe_form, action,
                        current_user):
    """ Do the same as before_update """
    return await before_update(
        db_session, field, before_form, tobe_form, action, current_user)


async def after_insert(db_session, field, before_form, tobe_form, action,
                       current_user):
    """ Do the same as after_update """
    return await after_update(
        db_session, field, before_form, tobe_form, action, current_user)


async def after_delete(db_session, field, before_form, tobe_form, action,
                       current_user):
    """
    Deletes all files uploaded for current row
    Returns:
        Object: Returns updated value of current field"""
    del before_form, action, current_user, db_session
    form_guid = str(tobe_form.guid)
    row_guid = str(uuid.UUID(str(tobe_form.row_guid)))
    row_folder = os.path.join(
        ax_misc.uploads_root_dir,
        'form_row_field_file',
        form_guid,
        row_guid
    )

    if os.path.exists(row_folder) is True:
        shutil.rmtree(row_folder)

    return field.value
