"""Defines Users Scheme and all mutations"""

import os
import sys
import re
import json
import zipfile
import shutil
import ast
import uuid
import asyncio
import urllib.request
from packaging import version
from loguru import logger
import graphene
import aiopubsub
import ruamel.yaml

from backend.model import AxForm, AxMetric, AxField, AxGrid, AxRole, AxState,\
    AxColumn, AxAction, AxAction2Role, AxState2Role, AxRoleFieldPermission,\
    Ax1tomReference, AxPage, AxFieldType
import backend.model as ax_model
import backend.dialects as ax_dialects
import backend.misc as ax_misc
from backend.auth import ax_admin_only
import backend.pubsub as ax_pubsub

this = sys.modules[__name__]

current_modal_guid = None
yaml = ruamel.yaml.YAML()
yaml.encoding = "utf-8"
yaml.allow_unicode = True
yaml.preserve_quotes = True


async def terminal_log(msg):
    """ Method used in AxTerminal. It sends message to vue via ws """
    if not this.current_modal_guid:
        return False

    ax_pubsub.publisher.publish(
        aiopubsub.Key('console_log'),
        {
            'text': msg,
            'modal_guid': current_modal_guid
        })
    await asyncio.sleep(0.01)


async def get_child_forms(db_session, form):
    """ returns flat list of all forms in tree """
    err = "marketplace_schema -> get_child_forms"
    with ax_model.try_catch(db_session, err) as db_session:
        ret_list = [form]
        sub_forms = db_session.query(AxForm).filter(
            AxForm.parent == form.guid
        ).all()

        for sub_form in sub_forms:
            # ret_list.append(sub_form)
            ret_list += await get_child_forms(db_session, sub_form)

        return ret_list


async def get_child_pages(db_session, page):
    """ returns flat list of all sub pages in tree """
    err = "marketplace_schema -> get_child_pages"
    with ax_model.try_catch(db_session, err) as db_session:
        ret_list = [page]
        sub_pages = db_session.query(AxPage).filter(
            AxPage.parent == page.guid
        ).all()

        for sub_page in sub_pages:
            # ret_list.append(sub_page)
            ret_list += await get_child_pages(db_session, sub_page)

        return ret_list


async def get_folders_and_forms(form_list):
    """ Splits flat form list to forms and folders """
    forms = []
    folders = []
    for form in form_list:
        if form.is_folder:
            folders.append(form)
        else:
            forms.append(form)
    return forms, folders


async def get_folders_dump(folders):
    """ returns list with serilized AxForm that are folders """
    ret_list = []
    for folder in folders:
        ret_list.append({
            "guid": str(folder.guid),
            "name": folder.name,
            "parent": str(folder.parent),
            "position": str(folder.position)
        })
    return ret_list


async def get_forms_db_names(forms):
    """ return flat list of form db_names """
    ret_list = []
    for form in forms:
        ret_list.append(form.db_name)
    return ret_list


async def save_page_py(page, pages_directory):
    """ Saves page code as file in package """
    if page.code:
        page_name = str(page.guid)
        if page.db_name:
            page_name = page.db_name
        page_md_path = pages_directory / f'page_{page_name}.md'
        with open(page_md_path, 'w', encoding="utf-8") as page_file:
            page_file.write(page.code)


async def dump_pages(db_session, package_directory, root_page):
    """ for each pages creates file and serilizes data, returns list """
    err = "marketplace_schema -> dump_pages"
    with ax_model.try_catch(db_session, err) as db_session:
        # Create AxPages folder
        ret_list = []
        pages_directory = package_directory / '_pages'
        os.makedirs(pages_directory)
        all_pages = await get_child_pages(db_session, root_page)

        for page in all_pages:
            ret_list.append({
                "guid": str(page.guid),
                "name": page.name,
                "db_name": page.db_name,
                "position": page.position,
                "parent": str(page.parent)
            })
            await save_page_py(page=page, pages_directory=pages_directory)

        return ret_list


async def dump_form(db_session, package_directory, form, include_data):
    """
        Creates dump of form and all related objects in separate folder ->
        /<db_name>/<db_name>.yaml contains most of data.
        # AxForm
        # AxField[]
        # AxMetric[]
        # AxGrid[], AxColumn[] - grid code saved as separate py files
        # AxRole[]
        # AxStates[], AxState2Role[]
        # AxActions[] - action code saved
        # AxRoleFieldPermission[]
        # Ax1tomReference[] - as tom_reference.yaml
        # SQL data - as data.yaml
    """
    err = "marketplace_schema -> dump_form"
    with ax_model.try_catch(db_session, err) as db_session:

        # Create directory
        form_path = package_directory / form.db_name
        if os.path.exists(form_path) is False:
            os.makedirs(form_path)
        form_yaml_path = form_path / f"{form.db_name}.yaml"
        with open(form_yaml_path, 'w', encoding="utf-8") as yaml_file:
            yaml_dict = {}
            # AxForm
            yaml_dict["AxForm"] = {
                "guid": str(form.guid),
                "name": form.name,
                "db_name": form.db_name,
                "parent": str(form.parent),
                "position": form.position,
                "tom_label": form.tom_label,
                "icon": form.icon,
            }

            # AxField[]
            yaml_dict["AxFields"] = []
            metric_fields = []
            for field in form.fields:
                yaml_dict["AxFields"].append({
                    "guid": str(field.guid),
                    "name": field.name,
                    "db_name": field.db_name,
                    "position": field.position,
                    "options_json": field.options_json,
                    "private_options_json": field.private_options_json,
                    "field_type_tag": field.field_type_tag,
                    "is_tab": field.is_tab,
                    "is_required": field.is_required,
                    "is_whole_row": field.is_whole_row,
                    "parent": str(field.parent)
                })

                if field.field_type_tag in ['AxNum']:
                    metric_fields.append(field)

            # AxMetric
            yaml_dict["AxMetrics"] = []
            for met_field in metric_fields:
                options = json.loads(met_field.private_options_json)
                key = options.get('counterKey')
                if key:
                    ax_metric = db_session.query(AxMetric).filter(
                        AxMetric.key == key
                    ).first()

                    if ax_metric:
                        yaml_dict["AxMetrics"].append({
                            "guid": str(ax_metric.guid),
                            "key": ax_metric.key,
                            "value": ax_metric.value
                        })

            # AxGrid[], AxColumns[]
            yaml_dict["AxGrids"] = []
            for grid in form.grids:
                columns = []
                for col in grid.columns:
                    columns.append({
                        "guid": str(col.guid),
                        "position": col.position,
                        "options_json": col.options_json,
                        "field_guid": str(col.field_guid),
                        "column_type": col.column_type,
                        "aggregation_type": col.aggregation_type
                    })

                yaml_dict["AxGrids"].append({
                    "guid": str(grid.guid),
                    "name": grid.name,
                    "db_name": grid.db_name,
                    "position": grid.position,
                    "options_json": grid.options_json,
                    "is_default_view": grid.is_default_view,
                    "columns": columns
                })

                if grid.code:
                    grid_py_path = form_path / f'grid_{grid.db_name}.py'
                    with open(grid_py_path, 'w', encoding="utf-8") as grid_file:
                        grid_file.write(grid.code)

            # AxRoles[]
            yaml_dict["AxRoles"] = []
            for role in form.roles:
                yaml_dict["AxRoles"].append({
                    "guid": str(role.guid),
                    "name": role.name,
                    "icon": role.icon,
                    "is_dynamic": role.is_dynamic
                })
                if role.code:
                    role_py_path = form_path / f'role_{role.db_name}.py'
                    with open(role_py_path, 'w', encoding="utf-8") as role_file:
                        role_file.write(role.code)

            # AxStates[]
            yaml_dict["AxStates"] = []
            for state in form.states:
                role_guids = []
                for state_role in state.roles:
                    role_guids.append(str(state_role.guid))
                yaml_dict["AxStates"].append({
                    "guid": str(state.guid),
                    "name": state.name,
                    "is_start": state.is_start,
                    "is_deleted": state.is_deleted,
                    "is_all": state.is_all,
                    "x": state.x,
                    "y": state.y,
                    "roles": role_guids
                })

            # AxActions[]
            yaml_dict["AxActions"] = []
            for action in form.actions:
                role_guids = []
                for action_role in action.roles:
                    role_guids.append(str(action_role.guid))
                yaml_dict["AxActions"].append({
                    "guid": str(action.guid),
                    "name": action.name,
                    "db_name": action.db_name,
                    "from_state_guid": str(action.from_state_guid),
                    "to_state_guid": str(action.to_state_guid),
                    "confirm_text": action.confirm_text,
                    "close_modal": action.close_modal,
                    "icon": action.icon,
                    "radius": action.radius,
                    "roles": role_guids
                })

                # save_action_py
                if action.code:
                    action_id = str(action.guid)
                    if action.db_name:
                        action_id = action.db_name
                    action_py_path = form_path / f'action_{action_id}.py'
                    with open(action_py_path, 'w', encoding="utf-8") as a_file:
                        a_file.write(action.code)

            # AxRoleFieldPermission[]
            yaml_dict["AxRoleFieldPermission"] = []
            for perm in form.permissions:
                yaml_dict["AxRoleFieldPermission"].append({
                    "role_guid": str(perm.role_guid),
                    "state_guid": str(perm.state_guid),
                    "field_guid": str(perm.field_guid),
                    "read": perm.read,
                    "edit": perm.edit
                })

            yaml.dump(yaml_dict, yaml_file)

            if include_data:
                # Ax1tomReference[]
                tom_references = db_session.query(Ax1tomReference).filter(
                    Ax1tomReference.form_guid == form.guid
                ).all()
                if tom_references:
                    clean_tom = []
                    for tom in tom_references:
                        clean_tom.append({
                            "guid": str(tom.guid),
                            "field_guid": str(tom.field_guid),
                            "row_guid": str(tom.row_guid),
                            "child_guid": str(tom.child_guid)
                        })
                    tom_path = form_path / f'tom_reference.yaml'
                    with open(tom_path, 'w', encoding="utf-8") as tom_file:
                        yaml.dump(clean_tom, tom_file)

                # SQL data
                data_result = db_session.execute(
                    f'SELECT * FROM "{form.db_name}"')
                if data_result:
                    def clear_value(val):
                        # if isinstance(val, uuid.UUID):
                        if val is None:
                            return None
                        if isinstance(val, (int, float, complex, bool)):
                            return val
                        return str(val)

                    clean_result = []
                    for row in data_result:
                        clean_row = {}
                        for key, value in row.items():
                            clean_row[key] = clear_value(value)
                        clean_result.append(clean_row)

                    data_path = form_path / f'data.yaml'
                    with open(data_path, 'w', encoding="utf-8") as data_file:
                        yaml.dump(clean_result, data_file)


async def do_create_readme(root_page, package_directory):
    """ Create Readme.md from root_page code """
    readme_path = package_directory / f'README.md'
    with open(readme_path, 'w', encoding="utf-8") as readme_file:
        readme_file.write(root_page.code)


class CreateMarketplaceApplication(graphene.Mutation):
    """ Creates archive with marketpalce application"""
    class Arguments:  # pylint: disable=missing-docstring
        folder_guid = graphene.String()
        name = graphene.String()
        version = graphene.String()
        db_name = graphene.String()
        root_page = graphene.String(required=False)
        include_data = graphene.Boolean()
        create_readme = graphene.Boolean()

    ok = graphene.Boolean()
    download_url = graphene.String()

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = "marketplace_schema -> CreateMarketplaceApplication"
        code_name = args.get('db_name')
        root_page_db_name = args.get('root_page')
        unique_guid = str(uuid.uuid4())
        include_data = args.get('include_data')
        create_readme = args.get('create_readme')

        with ax_model.try_catch(info.context['session'], err) as db_session:
            # Create tmp folder for new package
            archive_directory = ax_misc.tmp_root_dir / unique_guid
            package_directory = archive_directory / 'archive_me' / code_name
            dir_to_zip = archive_directory / 'archive_me'
            os.makedirs(package_directory)

            # Get AxForms and folders to dump
            root_folder = db_session.query(AxForm).filter(
                AxForm.guid == ax_misc.guid_or_none(
                    str(args.get('folder_guid')))
            ).first()
            if not root_folder:
                raise Exception('Cant find app root folder')

            # AxPage[]
            # Get AxPage if db_name is provided
            pages_data = []
            root_page = None
            root_page_guid = None
            if root_page_db_name:
                root_page = db_session.query(AxPage).filter(
                    AxPage.db_name == root_page_db_name
                ).first()

                if not root_page:
                    raise Exception('Cant find app root page')

                # Сreate readme.md
                if create_readme:
                    await do_create_readme(
                        root_page=root_page,
                        package_directory=package_directory)

                root_page_guid = str(root_page.guid)
                pages_data = await dump_pages(
                    db_session=db_session,
                    package_directory=package_directory,
                    root_page=root_page)

            all_forms = await get_child_forms(
                db_session=db_session, form=root_folder)
            app_forms, app_folders = await get_folders_and_forms(all_forms)

            # Create app.yaml
            app_yaml_path = package_directory / 'ax_app.yaml'
            with open(app_yaml_path, 'w', encoding="utf-8") as yaml_file:
                app_info = {
                    "Code name": code_name,
                    "Root folder": args.get('folder_guid'),
                    "Forms": await get_forms_db_names(app_forms),
                    "Folders": await get_folders_dump(app_folders),
                    "Root page": root_page_guid,
                    "Pages": pages_data,
                    "Ax version": os.environ.get('AX_VERSION')
                }
                yaml.dump(app_info, yaml_file)

            for form in app_forms:
                await dump_form(
                    db_session=db_session,
                    package_directory=package_directory,
                    form=form,
                    include_data=include_data)

            # version_str = str(app_version).replace(',', '-')
            # app_file_name = f'{code_name}-{version_str}.zip'
            app_file_name = f'{code_name}.zip'
            output_file_path = archive_directory / app_file_name

            await ax_misc.zip_folder(
                output_filename=output_file_path,
                source_dir=dir_to_zip)

            shutil.rmtree(dir_to_zip)

            url = f'/api/file/null/null/null/{unique_guid}/{app_file_name}'
            return CreateMarketplaceApplication(download_url=url, ok=True)



async def create_page(
        db_session, page, package_directory, ax_root_guid, app_root_guid):
    """ Create AxPage from application package data """
    err = "marketplace_schema -> create_page"
    with ax_model.try_catch(db_session, err) as db_session:
        code = None
        page_name = str(page['guid'])
        if page['db_name']:
            page_name = page['db_name']
        page_md_path = package_directory / '_pages' / f'page_{page_name}.md'
        if os.path.exists(page_md_path):
            with open(page_md_path, 'r', encoding="utf-8") as page_file:
                code = page_file.read()

        existing_page = db_session.query(AxPage).filter(
            AxPage.guid == ax_misc.guid_or_none(page['guid'])
        ).first()

        if existing_page:
            existing_page.name = page['name']
            existing_page.db_name = page['db_name']
            existing_page.position = int(page['position'] or 0)
            existing_page.parent = ax_misc.guid_or_none(page['parent'])
            existing_page.code = code
        else:
            cur_parent = page['parent']
            if page['guid'] == app_root_guid:
                cur_parent = ax_root_guid

            new_page = AxPage()
            new_page.guid = ax_misc.guid_or_none(page['guid'])
            new_page.name = page['name']
            new_page.db_name = page['db_name']
            new_page.position = int(page['position'] or 0)
            new_page.parent = ax_misc.guid_or_none(cur_parent)
            new_page.code = code
            db_session.add(new_page)


async def create_folder(db_session, folder):
    """ Create or update AxForm that is folder """
    err = "marketplace_schema -> create_folder"
    with ax_model.try_catch(db_session, err) as db_session:
        existing_folder = db_session.query(AxForm).filter(
            AxForm.guid == ax_misc.guid_or_none(folder['guid'])
        ).filter(
            AxForm.is_folder.is_(True)
        ).first()

        if existing_folder:
            existing_folder.name = folder['name']
        else:
            new_folder = AxForm()
            new_folder.guid = ax_misc.guid_or_none(folder['guid'])
            new_folder.name = folder['name']
            new_folder.is_folder = True
            new_folder.position = int(folder['position'] or 0)
            new_folder.parent = ax_misc.guid_or_none(folder['parent'])
            db_session.add(new_folder)


async def create_form(db_session, form):
    """ Create or update AxForm """
    err = "marketplace_schema -> create_form"
    with ax_model.try_catch(db_session, err) as db_session:
        existing_form = db_session.query(AxForm).filter(
            AxForm.guid == ax_misc.guid_or_none(form['guid'])
        ).first()
        new_form = None
        form_is_new = False

        if existing_form:
            existing_form.name = form['name']
            existing_form.tom_label = form['tom_label']
            existing_form.icon = form['icon']
        else:
            form_is_new = True
            new_form = AxForm()
            new_form.guid = ax_misc.guid_or_none(form['guid'])
            new_form.name = form['name']
            new_form.db_name = form['db_name']
            new_form.position = int(form['position'] or 0)
            new_form.parent = ax_misc.guid_or_none(form['parent'])
            new_form.tom_label = form['tom_label']
            new_form.icon = form['icon']
            db_session.add(new_form)

            await ax_dialects.dialect.create_data_table(
                db_session=db_session,
                db_name=form['db_name'])

            db_session.commit()

        ret_form = existing_form or new_form
        return form_is_new, ret_form


async def create_metric(db_session, metric):
    """ Create AxMetric if not exists """
    err = "marketplace_schema -> create_metric"
    with ax_model.try_catch(db_session, err) as db_session:
        existing_metric = db_session.query(AxMetric).filter(
            AxMetric.guid == ax_misc.guid_or_none(metric['guid'])
        ).first()

        if not existing_metric:
            new_metric = AxMetric()
            new_metric.guid = ax_misc.guid_or_none(metric['guid'])
            new_metric.key = metric['key']
            new_metric.value = metric['value']
            db_session.add(new_metric)


async def create_field(db_session, ax_form, field):
    """ Create or update AxField """
    err = "marketplace_schema -> create_field"
    with ax_model.try_catch(db_session, err) as db_session:
        existing_field = db_session.query(AxField).filter(
            AxField.guid == ax_misc.guid_or_none(field['guid'])
        ).first()

        if existing_field:
            existing_field.name = field['name']
            existing_field.options_json = field['options_json']
            existing_field.private_options_json = field['private_options_json']
            existing_field.is_required = field['is_required']
            existing_field.is_whole_row = field['is_whole_row']
            existing_field.parent = ax_misc.guid_or_none(field['parent'])
            existing_field.position = int(field['position'] or 0)
        else:
            new_field = AxField()
            new_field.guid = ax_misc.guid_or_none(field['guid'])
            new_field.form_guid = ax_form.guid
            new_field.name = field['name']
            new_field.db_name = field['db_name']
            new_field.options_json = field['options_json']
            new_field.private_options_json = field['private_options_json']
            new_field.field_type_tag = field['field_type_tag']
            new_field.is_tab = field['is_tab']
            new_field.is_required = field['is_required']
            new_field.is_whole_row = field['is_whole_row']
            new_field.parent = ax_misc.guid_or_none(field['parent'])
            new_field.position = int(field['position'] or 0)
            db_session.add(new_field)

            # Field is not tab
            if field['field_type_tag']:
                ax_field_type = db_session.query(AxFieldType).filter(
                    AxFieldType.tag == field['field_type_tag']
                ).first()

                if not ax_field_type.is_virtual:
                    await ax_dialects.dialect.add_column(
                        db_session=db_session,
                        table=ax_form.db_name,
                        db_name=field['db_name'],
                        type_name=ax_field_type.value_type)

                    db_session.commit()


async def create_column(db_session, grid_guid, column):
    """ Create or update AxColumn """
    err = "marketplace_schema -> create_column"
    with ax_model.try_catch(db_session, err) as db_session:
        existing_column = db_session.query(AxColumn).filter(
            AxColumn.guid == ax_misc.guid_or_none(column['guid'])
        ).first()
        new_column = None

        if existing_column:
            existing_column.position = int(column['position'] or 0)
            existing_column.options_json = column['options_json']
            existing_column.column_type = column['column_type']
            existing_column.aggregation_type = column['aggregation_type']
        else:
            new_column = AxColumn()
            new_column.guid = ax_misc.guid_or_none(column['guid'])
            new_column.position = int(column['position'] or 0)
            new_column.options_json = column['options_json']
            new_column.field_guid = ax_misc.guid_or_none(column['field_guid'])
            new_column.grid_guid = ax_misc.guid_or_none(grid_guid)
            new_column.column_type = column['column_type']
            new_column.aggregation_type = column['aggregation_type']
            db_session.add(new_column)


async def create_grid(db_session, form_directory, ax_form, grid):
    """ Create or update AxGrid """
    err = "marketplace_schema -> create_grid"
    with ax_model.try_catch(db_session, err) as db_session:
        code = None
        existing_grid = db_session.query(AxGrid).filter(
            AxGrid.guid == ax_misc.guid_or_none(grid['guid'])
        ).first()
        new_grid = None

        grid_py_path = form_directory / f'grid_{grid["db_name"]}.py'
        if os.path.exists(grid_py_path):
            with open(grid_py_path, 'r', encoding="utf-8") as grid_file:
                code = grid_file.read()

        if existing_grid:
            existing_grid.name = grid['name']
            existing_grid.db_name = grid['db_name']
            existing_grid.position = int(grid['position'] or 0)
            existing_grid.options_json = grid['options_json']
            existing_grid.code = code
            existing_grid.is_default_view = grid['is_default_view']
        else:
            new_grid = AxGrid()
            new_grid.guid = ax_misc.guid_or_none(grid['guid'])
            new_grid.name = grid['name']
            new_grid.db_name = grid['db_name']
            new_grid.position = int(grid['position'] or 0)
            new_grid.options_json = grid['options_json']
            new_grid.code = code
            new_grid.form_guid = ax_form.guid
            new_grid.is_default_view = grid['is_default_view']
            db_session.add(new_grid)

    for column in grid['columns']:
        await create_column(
            db_session=db_session,
            grid_guid=grid['guid'],
            column=column)

    return existing_grid or new_grid


async def create_role(db_session, ax_form, role, form_path):
    """ Create or update AxRole """
    err = "marketplace_schema -> create_role"
    with ax_model.try_catch(db_session, err) as db_session:
        existing_role = db_session.query(AxRole).filter(
            AxRole.guid == ax_misc.guid_or_none(role['guid'])
        ).first()
        new_role = None

        code = None
        role_db_name = re.sub(r'[\W_]+', '', role['name'])
        role_py_path = form_path / f'role_{role_db_name}.py'
        if os.path.exists(role_py_path):
            with open(role_py_path, 'r', encoding="utf-8") as role_file:
                code = role_file.read()

        if existing_role:
            existing_role.name = role['name']
            existing_role.icon = role.get('icon', None)
        else:
            new_role = AxRole()
            new_role.guid = ax_misc.guid_or_none(role['guid'])
            new_role.name = role['name']
            new_role.form_guid = ax_form.guid
            new_role.icon = role.get('icon', None)
            new_role.is_dynamic = role.get('is_dynamic', False)
            new_role.code = code
            db_session.add(new_role)


async def create_state2role(db_session, state_guid, role_guid):
    """ Create or update AxState2Role """
    err = "marketplace_schema -> create_state2role"
    with ax_model.try_catch(db_session, err) as db_session:
        existing_s2r = db_session.query(AxState2Role).filter(
            AxState2Role.state_guid == ax_misc.guid_or_none(state_guid)
        ).filter(
            AxState2Role.role_guid == ax_misc.guid_or_none(role_guid)
        ).first()

        if not existing_s2r:
            new_s2r = AxState2Role()
            new_s2r.state_guid = ax_misc.guid_or_none(state_guid)
            new_s2r.role_guid = ax_misc.guid_or_none(role_guid)
            db_session.add(new_s2r)


async def create_state(db_session, ax_form, state):
    """ Create or update AxState """
    err = "marketplace_schema -> create_state"
    with ax_model.try_catch(db_session, err) as db_session:
        existing_state = db_session.query(AxState).filter(
            AxState.guid == ax_misc.guid_or_none(state['guid'])
        ).first()
        new_state = None

        if existing_state:
            existing_state.name = state['name']
            existing_state.x = float(state['x'] or 0)
            existing_state.y = float(state['y'] or 0)
        else:
            new_state = AxState()
            new_state.guid = ax_misc.guid_or_none(state['guid'])
            new_state.name = state['name']
            new_state.form_guid = ax_form.guid
            new_state.is_start = state['is_start']
            new_state.is_deleted = state['is_deleted']
            new_state.is_all = state['is_all']
            new_state.x = float(state['x'] or 0)
            new_state.y = float(state['y'] or 0)
            db_session.add(new_state)

        for role_guid in state['roles']:
            await create_state2role(
                db_session=db_session,
                state_guid=state['guid'],
                role_guid=role_guid)


async def create_action2role(db_session, action_guid, role_guid):
    """ Create or update AxAction2Role """
    err = "marketplace_schema -> create_action2role"
    with ax_model.try_catch(db_session, err) as db_session:
        existing_a2r = db_session.query(AxAction2Role).filter(
            AxAction2Role.action_guid == ax_misc.guid_or_none(action_guid)
        ).filter(
            AxAction2Role.role_guid == ax_misc.guid_or_none(role_guid)
        ).first()

        if not existing_a2r:
            new_a2r = AxAction2Role()
            new_a2r.action_guid = ax_misc.guid_or_none(action_guid)
            new_a2r.role_guid = ax_misc.guid_or_none(role_guid)
            db_session.add(new_a2r)


async def drop_actions(db_session, ax_form):
    """ Deletes all AxActions and AxAction2Role of form """
    err = "marketplace_schema -> drop_actions"
    with ax_model.try_catch(db_session, err) as db_session:
        for action in ax_form.actions:
            db_session.query(AxAction2Role).filter(
                AxAction2Role.action_guid == action.guid).delete()
            db_session.delete(action)


async def create_action(db_session, form_directory, ax_form, action):
    """ Creates new AxAction """
    err = "marketplace_schema -> create_action"
    with ax_model.try_catch(db_session, err) as db_session:
        code = None
        action_id = str(action['guid'])
        if action['db_name']:
            action_id = action['db_name']
        action_py_path = form_directory / f'action_{action_id}.py'

        if os.path.exists(action_py_path):
            with open(action_py_path, 'r', encoding="utf-8") as action_file:
                code = action_file.read()

        new_action = AxAction()
        new_action.guid = ax_misc.guid_or_none(action['guid'])
        new_action.name = action['name']
        new_action.db_name = action['db_name']
        new_action.form_guid = ax_form.guid
        new_action.from_state_guid = ax_misc.guid_or_none(
            action['from_state_guid'])
        new_action.to_state_guid = ax_misc.guid_or_none(
            action['to_state_guid'])
        new_action.code = code
        new_action.confirm_text = action['confirm_text']
        new_action.close_modal = action['close_modal']
        new_action.icon = action['icon']
        new_action.radius = float(action['radius'] or 0)
        db_session.add(new_action)

        for role_guid in action['roles']:
            await create_action2role(
                db_session=db_session,
                action_guid=action['guid'],
                role_guid=role_guid)


async def create_role_field_perm(db_session, ax_form, perm):
    """ AxRoleFieldPermission creaes new """
    err = "marketplace_schema -> create_role_field_perm"
    with ax_model.try_catch(db_session, err) as db_session:
        new_perm = AxRoleFieldPermission()
        new_perm.role_guid = ax_misc.guid_or_none(str(perm['role_guid']))
        new_perm.state_guid = ax_misc.guid_or_none(str(perm['state_guid']))
        new_perm.field_guid = ax_misc.guid_or_none(str(perm['field_guid']))
        new_perm.form_guid = ax_form.guid
        new_perm.read = perm['read']
        new_perm.edit = perm['edit']
        db_session.add(new_perm)


async def create_tom_references(db_session, ax_form, form_directory):
    """ # Ax1tomReference[] - only insert if not exists """
    err = "marketplace_schema -> create_tom_references"
    with ax_model.try_catch(db_session, err) as db_session:
        tom_yaml_path = form_directory / 'tom_reference.yaml'
        if not os.path.exists(tom_yaml_path):
            return False

        with open(tom_yaml_path, 'r', encoding="utf-8") as tom_yaml_file:
            tom_yaml = yaml.load(tom_yaml_file)
            for ref in tom_yaml:
                new_ref = Ax1tomReference()
                new_ref.form_guid = ax_form.guid
                new_ref.field_guid = ax_misc.guid_or_none(ref['field_guid'])
                new_ref.row_guid = ax_misc.guid_or_none(ref['row_guid'])
                new_ref.child_guid = ax_misc.guid_or_none(ref['child_guid'])
                new_ref.field_guid = ax_misc.guid_or_none(ref['field_guid'])
                db_session.add(new_ref)


def clean_yaml_value(row, field):
    """ When json is dumped to yaml is forced with double qoutes,
        but when readed - qoutes stays in string. We must remove them """
    value = row[field.db_name]
    if value and field.field_type.value_type == 'JSON':
        try:
            value = json.loads(value)
        except:
            try:
                value = ast.literal_eval(value)
            except:
                value_str = str(value)
                logger.error(
                    f'clean_yaml_value -> could not decode json {value_str}')
                value = None
    return value


async def insert_data(db_session, ax_form, form_directory):
    """ Inserts data from package """
    err = "marketplace_schema -> insert_data"
    with ax_model.try_catch(db_session, err) as db_session:
        data_yaml_path = form_directory / 'data.yaml'
        if not os.path.exists(data_yaml_path):
            return False

        with open(data_yaml_path, 'r', encoding="utf-8") as data_yaml_file:
            data_yaml = yaml.load(data_yaml_file)
            for row in data_yaml:
                tobe_form = db_session.query(AxForm).filter(
                    AxForm.guid == ax_form.guid
                ).first()

                for field in tobe_form.db_fields:
                    if field.db_name in row.keys():
                        field.value = clean_yaml_value(row=row, field=field)
                        field.needs_sql_update = True

                await ax_dialects.dialect.insert(
                    db_session=db_session,
                    form=tobe_form,
                    to_state_name=row["axState"],
                    new_guid=ax_misc.guid_or_none(row['guid']))


async def create_form_objects(db_session, form_name, package_directory):
    """ Creates or updates
        # AxForm - when update position and parent is ignored
        # AxField[] - when update - db_name is ignored
        # AxMetric[] - only insert if does not exist
        # AxGrid[], AxColumn[]
        # AxRole[]
        # AxStates[], AxState2Role[]
        # AxActions[] - deletes, creates new
        # AxRoleFieldPermission[] - deletes, creaes new
        # Ax1tomReference[] - insert if first install
        # SQL data - insert if first install
        """
    err = "marketplace_schema -> create_form_objects"
    with ax_model.try_catch(db_session, err) as db_session:
        form_directory = package_directory / form_name
        yaml_path = form_directory / f'{form_name}.yaml'
        with open(yaml_path, 'r', encoding="utf-8") as form_yaml_file:
            form_yaml = yaml.load(form_yaml_file)

            form_db_name = form_yaml["AxForm"]["db_name"]
            await terminal_log(f'\nCreating form [{form_db_name}] \n')

            # AxForm
            form_is_new = False
            form_is_new, ax_form = await create_form(
                db_session=db_session, form=form_yaml["AxForm"])

            # AxField[]
            await terminal_log(f'AxFields:\n')
            for field in form_yaml["AxFields"]:
                await create_field(
                    db_session=db_session,
                    ax_form=ax_form,
                    field=field)
                await terminal_log(f'    {field["db_name"]} ✔\n')

            # AxMetric[]
            for metric in form_yaml["AxMetrics"]:
                await create_metric(db_session=db_session, metric=metric)

            # AxGrid[], AxColumn[]
            await terminal_log(f'AxGrids:\n')
            for grid in form_yaml["AxGrids"]:
                await create_grid(
                    db_session=db_session,
                    form_directory=form_directory,
                    ax_form=ax_form,
                    grid=grid)
                await terminal_log(f'    {grid["db_name"]} ✔\n')

            # AxRole[]
            await terminal_log(f'AxRoles:\n')
            for role in form_yaml['AxRoles']:
                await create_role(
                    db_session=db_session,
                    ax_form=ax_form,
                    role=role,
                    form_path=form_directory)
                await terminal_log(f'    {role["name"]} ✔\n')

            # AxStates[]
            await terminal_log(f'AxStates:\n')
            for state in form_yaml['AxStates']:
                await create_state(
                    db_session=db_session,
                    ax_form=ax_form,
                    state=state)
                await terminal_log(f'    {state["name"]} ✔\n')

            # AxActions[] - deletes, creates new
            await terminal_log(f'AxActions:\n')
            await drop_actions(db_session=db_session, ax_form=ax_form)
            for action in form_yaml['AxActions']:
                await create_action(
                    db_session=db_session,
                    form_directory=form_directory,
                    ax_form=ax_form,
                    action=action)
                await terminal_log(f'    {action["name"]} ✔\n')

            db_session.commit()

            # AxRoleFieldPermission[] - deletes, creaes new
            for ax_perm in ax_form.permissions:
                db_session.delete(ax_perm)
            for perm in form_yaml['AxRoleFieldPermission']:
                await create_role_field_perm(
                    db_session,
                    ax_form,
                    perm)

            if form_is_new:
                await terminal_log(f'Creating data')
                # Ax1tomReference[] - insert if first install
                await create_tom_references(
                    db_session=db_session,
                    ax_form=ax_form,
                    form_directory=form_directory)

                # SQL data - insert if first install
                await insert_data(
                    db_session=db_session,
                    ax_form=ax_form,
                    form_directory=form_directory)
                await terminal_log(f' ->  ✔\n')
            else:
                await terminal_log(
                    f'Form already exists, data was not inserted')



async def check_existing_form(db_session, package_directory, form_db_name):
    """ Checks if AxForm with such db_name already exists. Aborts installation
        if found """
    form_directory = package_directory / form_db_name
    yaml_path = form_directory / f'{form_db_name}.yaml'
    form_guid = None
    with open(yaml_path, 'r', encoding="utf-8") as form_yaml_file:
        form_yaml = yaml.load(form_yaml_file)
        form_guid = form_yaml["AxForm"]["guid"]

    existing_form = db_session.query(AxForm).filter(
        AxForm.db_name == form_db_name
    ).first()

    if existing_form.guid != ax_misc.guid_or_none(form_guid):
        err = (f'Can not create AxForm [{form_db_name}]. Form with same '
               f'db_name already exists.\nInstallation is aborted ☠️')
        logger.exception(err)
        await terminal_log(f'\n\n\n{err}')
        raise Exception(err)


async def check_package(db_session, app_yaml, package_directory):
    """ Check if package can be installed """
    # Check ax version
    code_name = app_yaml["Code name"]
    app_ax_version = app_yaml["Ax version"]
    system_ax_version = os.environ.get('AX_VERSION')
    if version.parse(system_ax_version) < version.parse(app_ax_version):
        msg = (f'Error installing application [{code_name}].'
               f'Current version of Ax [{system_ax_version}] must be upgraded '
               f'to [{app_ax_version}] for this application. '
               f'\nInstallation is aborted ☠️')
        logger.exception(msg)
        await terminal_log(f'\n\n\n{msg}')
        raise Exception(msg)

    # Check if table names of application is already present in database
    ax_forms = db_session.query(AxForm).with_entities(AxForm.db_name).all()
    existing_db_names = [form.db_name for form in ax_forms]
    for form_db_name in app_yaml['Forms']:
        if form_db_name in existing_db_names:
            # Check if guid of existing form is same as application form
            await check_existing_form(
                db_session=db_session,
                package_directory=package_directory,
                form_db_name=form_db_name)
        else:
            # Check if table exists
            if ax_model.engine.dialect.has_table(ax_model.engine, form_db_name):
                err = (f'Database already contains table [{form_db_name}],'
                       f'but it is not registered as AxForm'
                       f'.\nInstallation is aborted ☠️')
                logger.exception(err)
                await terminal_log(f'\n\n\n{err}')
                raise Exception(err)


async def install_from_dir(db_session, app_dir):
    """ Installs app from yaml files in /tmp folder """
    import backend.schema as ax_schema
    with open(app_dir / 'ax_app.yaml', 'r', encoding="utf-8") as app_yaml_file:
        app_yaml = yaml.load(app_yaml_file)

        # Check if package can be installed
        await check_package(
            db_session=db_session,
            app_yaml=app_yaml,
            package_directory=app_dir)

        # Create pages
        await terminal_log('Creating pages:\n')
        ax_root_page = db_session.query(AxPage).filter(
            AxPage.parent.is_(None)
        ).first()
        ax_root_guid = None
        if ax_root_page:
            ax_root_guid = str(ax_root_page.guid)

        app_root_guid = app_yaml.get('Root page', None)
        for page in app_yaml.get('Pages', None):
            await create_page(
                db_session=db_session,
                page=page,
                package_directory=app_dir,
                ax_root_guid=ax_root_guid,
                app_root_guid=app_root_guid)
            await terminal_log(f'    {page["name"]} ✔\n')

        # Create folders
        await terminal_log('Creating folders:\n')
        for folder in app_yaml['Folders']:
            await create_folder(db_session=db_session, folder=folder)
            await terminal_log(f'    {folder["name"]} ✔\n')

        # For each form - create form
        for form_name in app_yaml['Forms']:
            await create_form_objects(
                db_session=db_session,
                form_name=form_name,
                package_directory=app_dir)

        ax_schema.init_schema(db_session)
        await terminal_log('------------------\n Application is installed!')



async def install_from_repo(db_session, repo_name):
    """ Installs marketplace application from github repo """
    tmp_dir = ax_misc.tmp_root_dir / str(uuid.uuid4())
    os.makedirs(tmp_dir)
    tmp_zip = tmp_dir / "installed_app.zip"
    archive_dir = tmp_dir / "package_archive"

    # Read archive data to ram
    await terminal_log(f'Downloading master from repo [{repo_name}]!\n\n')
    url = f'https://github.com/{repo_name}/archive/master.zip'
    filedata = urllib.request.urlopen(url)
    data_to_write = filedata.read()

    # Write archvive data to tmp file
    with open(tmp_zip, 'wb') as file:
        file.write(data_to_write)

    # Unzip tmp file
    await terminal_log(f'Download success\n\n')
    with zipfile.ZipFile(tmp_zip, "r") as zip_ref:
        zip_ref.extractall(archive_dir)

    app_code_name = os.listdir(archive_dir)[0]
    app_dir = archive_dir / app_code_name
    await install_from_dir(db_session=db_session, app_dir=app_dir)



class InstallFromPackage(graphene.Mutation):
    """ Installs marketplace application from zip archive uploaded
        to tmp folder """
    class Arguments:  # pylint: disable=missing-docstring
        file_guid = graphene.String()
        modal_guid = graphene.String()

    ok = graphene.Boolean()
    msg = graphene.String()

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = 'Error in gql mutation - InstallFromPackage.'
        with ax_model.try_catch(info.context['session'], err) as db_session:
            del info
            this.current_modal_guid = args.get('modal_guid')
            file_guid = args.get('file_guid')
            tmp_dir = ax_misc.tmp_root_dir / file_guid
            file_name = os.listdir(tmp_dir)[0]
            temp_path = tmp_dir / file_name
            archive_dir = tmp_dir / "package_archive"

            with zipfile.ZipFile(temp_path, "r") as zip_ref:
                zip_ref.extractall(archive_dir)

            app_code_name = os.listdir(archive_dir)[0]
            app_dir = archive_dir / app_code_name
            await install_from_dir(db_session=db_session, app_dir=app_dir)
            return InstallFromPackage(msg='InstallFromPackage - OK', ok=True)


class InstallFromRepo(graphene.Mutation):
    """ Installs marketplace application from github repo """
    class Arguments:  # pylint: disable=missing-docstring
        repo_name = graphene.String()
        modal_guid = graphene.String()

    ok = graphene.Boolean()
    msg = graphene.String()

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring

        err = 'Error in gql mutation - InstallFromRepo.'
        with ax_model.try_catch(info.context['session'], err) as db_session:
            del info
            this.current_modal_guid = args.get('modal_guid')
            repo_name = args.get('repo_name')
            await install_from_repo(db_session=db_session, repo_name=repo_name)
            return InstallFromRepo(msg='InstallFromRepo - OK', ok=True)



class MarketplaceQuery(graphene.ObjectType):
    """ queryes"""


class MarketplaceMutations(graphene.ObjectType):
    """Contains all AxUser mutations"""
    create_marketplace_application = CreateMarketplaceApplication.Field()
    install_from_package = InstallFromPackage.Field()
    install_from_repo = InstallFromRepo.Field()
