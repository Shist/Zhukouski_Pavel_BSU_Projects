"""Miscellaneous functions
"""

import os
import sys
import re
import uuid
import zipfile
import shutil
from pathlib import Path
from datetime import datetime
import asyncio
import graphene
# import graphene_sqlalchemy
import pytz
import yaml
from loguru import logger
# from dotmap import DotMap
import aiohttp

this = sys.modules[__name__]
root_path = None
timezone = None
tmp_root_dir = None
uploads_root_dir = None


def init_misc(timezone_name, tmp_absolute_path, uploads_absolute_path) -> None:
    """Inititate time_zone, root_path"""

    try:
        this.uploads_root_dir = path('uploads')
        if uploads_absolute_path is not None:
            this.uploads_root_dir = str(Path(uploads_absolute_path))
        if not server_is_app_engine():
            if not os.path.exists(this.uploads_root_dir):
                os.makedirs(this.uploads_root_dir)

        if not os.access(this.uploads_root_dir, os.W_OK):
            raise PermissionError(
                f'Cant write to directory - {this.uploads_root_dir}')
    except Exception:
        logger.exception(
            'Uploads folder does not exist and Ax cant create it')
        raise

    try:
        this.tmp_root_dir = path('tmp')
        if tmp_absolute_path is not None:
            this.tmp_root_dir = str(Path(tmp_absolute_path))
        if not os.path.exists(this.tmp_root_dir):
            if not server_is_app_engine():
                os.makedirs(this.tmp_root_dir)
    except Exception:
        logger.exception(
            'Tmp folder does not exist and Ax cant create it')
        raise

    if timezone_name not in pytz.common_timezones:
        logger.error(
            'Timezone {tz} not valid. Falling back to UTC.', tz=timezone_name)
        this.timezone = 'UTC'

    this.timezone = pytz.timezone(timezone_name)


def date(_date: datetime = datetime.now()) -> datetime:
    """Localise python datetime"""
    localized_date = this.timezone.localize(_date, is_dst=None)
    return localized_date


def path(_path: str = '') -> str:
    """Get correct absolute path.

    Agrs:
        _path (str, optional): Defaults to ''. Path relative to module root.

    Returns:
        str: Absolute path to specified file or directory
    Examples:
        Access module files like path('backend/schemas/user_schema.py')
    """
    if this.root_path is None:
        this.root_path = Path(__file__).resolve().parent.parent
        # logger.debug('File path = {root}', root=Path(__file__))
    return root_path / _path


def server_is_app_engine() -> bool:
    """Is Sanic is running on Google App Engine Standard"""
    return os.getenv("GAE_VERSION") or None


def load_configuration() -> None:
    """Function that loads ax application configuration from app.yaml

    If application is running on Google App Engine, all params from
    env_variables section of app.yaml will be loaded as enviroment variables.
    If application is running outside of App Engine then we must load
    variables ourselves.

    Args:
        app_yaml_location (str): Path to app.yaml location.

    Returns:
        bool: The return value. True for success.
    Examples:
        Access configuration variables like os.environ['AX_VERSION']

    Raises:
        FileNotFoundError: Cant find app.yaml
        ValueError: Cant parse app.yaml
        LookupError: No env_variables section in app.yaml
    """
    app_yaml = path('app.yaml')
    app_template_yaml = path('app.template.yaml')

    if not os.path.isfile(app_yaml):
        # os.rename(app_template_yaml, app_yaml)
        shutil.copyfile(app_template_yaml, app_yaml)

    if not os.path.isfile(app_yaml):
        raise FileNotFoundError('Configuration failed, app.yaml not found')

    if not server_is_app_engine():
        with open(app_yaml, 'r') as stream:
            try:
                yaml_vars = yaml.safe_load(stream)
                if 'env_variables' not in yaml_vars:
                    err = 'Configuration failed, no env_variables in app.yaml'
                    logger.error(err)
                    raise LookupError(err)
                for key, value in yaml_vars['env_variables'].items():
                    if value:
                        os.environ[key] = str(value)
            except yaml.YAMLError as exc:
                err = 'Configuration failed, cant parse yaml - ' + exc
                logger.error(err)
                raise ValueError(err)


def convert_column_to_string(type, column, registry=None):  # pylint: disable=redefined-builtin
    """This functions is needed to convert UUID column to String column
    for SQL Alchemy"""
    del type, column, registry
    return graphene.String


def string_is_guid(string_guid):
    """Checks if string is valid guid can be
     302a4299736e4ef384fca9f400e84b24 or 302a4299-736e-4ef3-84fc-a9f400e84b24

    Returns:
        [str]: version of uuid or None
    """
    try:
        return uuid.UUID(str(string_guid)).version
    except ValueError:
        return None


def guid_or_none(string_guid):
    """ returns uuid or None """
    if string_is_guid(string_guid):
        return uuid.UUID(str(string_guid))
    return None


async def zip_folder(output_filename, source_dir):
    """ Archive folder """
    relroot = source_dir
    with zipfile.ZipFile(output_filename, "w", zipfile.ZIP_DEFLATED) as z_file:
        for root, dirs, files in os.walk(source_dir):
            del dirs
            # add directory (needed for empty dirs)
            # zip.write(root, os.path.relpath(root, relroot))
            for file in files:
                filename = os.path.join(root, file)
                if os.path.isfile(filename):  # regular files only
                    arcname = os.path.join(
                        os.path.relpath(root, relroot), file)
                    z_file.write(filename, arcname)


async def get_tom_label(form):
    """ Gets AxForm with field values and constructs tom_label by replacing
        {{tags}} with field values """
    tom_label_modified = form.tom_label.replace(
        "{{ax_form_name}}", form.name
    ).replace(
        "{{ax_db_name}}", form.db_name
    ).replace(
        "{{guid}}", str(form.row_guid)
    )

    tags = re.findall("{{(.*?)}}", tom_label_modified)
    for field in form.fields:
        if field.db_name in tags:
            tom_label_modified = tom_label_modified.replace(
                "{{" + field.db_name + "}}", str(field.value)
            )

    return tom_label_modified


async def get_ax_host():
    """ Returns ax instance url with method and port. From app.yaml """
    return os.environ.get('AX_URL')


async def fetch(url):
    """ fetchs web-page by url """
    try:
        timeout = aiohttp.ClientTimeout(total=20)
        async with aiohttp.ClientSession() as session:
            async with session.get(url, timeout=timeout) as response:
                return await response.text()
    except (asyncio.TimeoutError, ConnectionRefusedError):
        return None


async def post_json(url, data, timeout=20):
    """ Make post request with json data """
    try:
        timeout = aiohttp.ClientTimeout(total=timeout)
        async with aiohttp.ClientSession() as session:
            async with session.post(
                    url, json=data, timeout=timeout) as response:
                return await response.text()
    except (asyncio.TimeoutError, ConnectionRefusedError):
        return None
