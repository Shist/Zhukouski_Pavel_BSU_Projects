"""
Module for database migration using Alembic
It checks if database is accesible.
Creates sqlite database if needed.
Checks if database have SqlAlchemy tables. If not - it creates tables.
    When tables are created, they are filled with default values.
    Such as AxFieldType are filled with field types.
Checks that current Database schema fits SqlAlchemy schema. If it is not,
    it tryes to upgrade it by running alembic migration scripts.

"""
import os
import sys
import uuid
import asyncio
import json
from loguru import logger
import yaml
from passlib.hash import pbkdf2_sha256
from alembic.config import Config
from alembic.migration import MigrationContext
from alembic.autogenerate import compare_metadata
from alembic import command
import backend.model as ax_model
import backend.misc as ax_misc
import backend.auth as ax_auth
from backend.model import AxAlembicVersion, AxFieldType, AxUser, AxGroup2Users,\
    AxPage, AxPage2Users, AxForm, AxAction, AxGrid, AxRole

this = sys.modules[__name__]
alembic_cfg = None
stats = None


def init_alembic_config() -> None:
    """Create Alembic config"""
    try:
        ini_path = ax_misc.path("alembic.ini")
        this.alembic_cfg = Config(ini_path)
        alembic_folder = ax_misc.path("backend/alembic")
        this.alembic_cfg.set_main_option(
            'script_location', str(alembic_folder))
    except Exception:
        logger.exception('Error initating alembic config.')
        raise


def tables_exist() -> bool:
    """Checks if database tables are created"""
    try:
        tables_created = ax_model.engine.dialect.has_table(
            ax_model.engine, '_ax_alembic_version')
        if tables_created:
            return True
        else:
            return False
    except Exception:
        logger.exception('Error in detecting if database tables are created')
        raise


def create_tables() -> None:
    """Create database and create baseline version in Alembic"""
    with ax_model.scoped_session("migration -> create_tables") as db_session:
        if os.environ.get('AX_DB_REVISION') is None:
            msg = 'Cant find AX_DB_REVISION in enviroment variables or app.yaml'
            logger.error(msg)
            raise Exception(msg)

        # ax_model.Base.query = db_session.query_property()
        ax_model.Base.metadata.create_all(ax_model.engine)
        first_version = AxAlembicVersion()
        first_version.version_num = os.environ.get('AX_DB_REVISION')
        db_session.add(first_version)

        logger.info('Ax tables not found. Creating database tables.')
        return True


def create_default_pages():
    """ Create default page """
    with ax_model.scoped_session(
            "migration -> create_default_pages") as db_session:
        index_page = AxPage()
        index_page.name = "Index Page"
        index_page.code = (f"<h1>Welcome to Ax pages</h1>\n"
                           f"<br/><br/>Hello world")
        db_session.add(index_page)

        all_user = db_session.query(AxUser).filter(
            AxUser.is_all_users.is_(True)
        ).first()

        p2u = AxPage2Users()
        p2u.page_guid = index_page.guid
        p2u.user_guid = all_user.guid
        db_session.add(p2u)

        db_session.commit()


def create_default_users():
    """ Create Admin group, Default admin, Everyone, All users """
    msg = "Error -> Migration -> create_default_users"
    with ax_model.scoped_session(msg) as db_session:
        # Admin group
        admin_group = AxUser()
        # admin_group.short_name = 'users.admin-group-name'
        admin_group.short_name = 'Administrators'
        admin_group.is_group = True
        admin_group.is_admin = True
        db_session.add(admin_group)

        # Default admin
        admin = AxUser()
        admin.email = 'default@ax-workflow.com'
        admin.password = pbkdf2_sha256.hash('deleteme')
        admin.name = 'Default Administrator. Delete this user.'
        admin.short_name = 'Default Admin'
        db_session.add(admin)

        db_session.commit()

        group_user = AxGroup2Users()
        group_user.group_guid = admin_group.guid
        group_user.user_guid = admin.guid
        db_session.add(group_user)

        # Everyone
        everyone_group = AxUser()
        # everyone_group.short_name = 'users.everyone-group-name'
        everyone_group.short_name = 'Everyone'
        everyone_group.is_group = True
        everyone_group.is_everyone = True
        db_session.add(everyone_group)

        # All users
        all_group = AxUser()
        # all_group.short_name = 'users.all-users-group-name'
        all_group.short_name = 'All users'
        all_group.is_group = True
        all_group.is_all_users = True
        db_session.add(all_group)
        db_session.commit()


def create_field_type(db_session, item):
    """ Create AxFieldType from yaml data """
    db_session.add(AxFieldType(
        tag=item.get('tag', None),
        name=item.get('name', None),
        position=item.get('position', 0),
        default_name=item.get('default_name', None),
        default_db_name=item.get('default_db_name', ''),
        value_type=item.get('value_type', ''),
        parent=item.get('parent', ''),
        icon=item.get('icon', ''),
        comparator=item.get('comparator', ''),
        virtual_source=item.get('virtual_source', None),
        is_virtual=item.get('is_virtual', False),
        is_readonly=item.get('is_readonly', False),
        is_inline_editable=item.get('is_inline_editable', False),
        is_backend_available=item.get('is_backend_available', False),
        is_display_backend_avalible=item.get(
            'is_display_backend_avalible', False),
        is_columnn_avalible=item.get('is_columnn_avalible', False),
        is_updated_always=item.get('is_updated_always', False),
        is_group=item.get('is_group', False),
        is_always_whole_row=item.get('is_always_whole_row', False)
    ))


def update_field_type(field_types, item):
    """ Update AxFieldType from yaml data if needed """
    for ax_field in field_types:
        if ax_field.tag == item['tag']:
            # TODO do this from list in loop!
            if 'name' in item and ax_field.name != item['name']:
                ax_field.name = item['name']
            if 'position' in item and ax_field.position != item['position']:
                ax_field.position = item['position'],
            if ('default_name' in item
                    and ax_field.default_name != item['default_name']):
                ax_field.name = item['default_name']
            if ('default_db_name' in item
                    and ax_field.default_db_name != item['default_db_name']):
                ax_field.default_db_name = item['default_db_name']
            if ('value_type' in item
                    and ax_field.value_type != item['value_type']):
                ax_field.value_type = item['value_type']
            if 'parent' in item and ax_field.parent != item['parent']:
                ax_field.parent = item['parent']
            if 'icon' in item and ax_field.icon != item['icon']:
                ax_field.icon = item['icon']
            if ('comparator' in item
                    and ax_field.comparator != item['comparator']):
                ax_field.comparator = item['comparator']
            if ('virtual_source' in item and
                    ax_field.virtual_source != item['virtual_source']):
                ax_field.virtual_source = item['virtual_source']
            if ('is_virtual' in item and
                    ax_field.is_virtual != item['is_virtual']):
                ax_field.is_virtual = item['is_virtual']
            if ('is_readonly' in item and
                    ax_field.is_readonly != item['is_readonly']):
                ax_field.is_readonly = item['is_readonly']
            if ('is_inline_editable' in item
                    and ax_field.is_inline_editable
                    != item['is_inline_editable']):
                ax_field.is_inline_editable = item['is_inline_editable']
            if ('is_backend_available' in item
                    and ax_field.is_backend_available
                    != item['is_backend_available']):
                ax_field.is_backend_available = item['is_backend_available']
            if ('is_display_backend_avalible' in item
                    and ax_field.is_display_backend_avalible
                    != item['is_display_backend_avalible']):
                the_item = item['is_display_backend_avalible']
                ax_field.is_display_backend_avalible = the_item
            if ('is_columnn_avalible' in item and
                    ax_field.is_columnn_avalible
                    != item['is_columnn_avalible']):
                ax_field.is_columnn_avalible = item['is_columnn_avalible']
            if ('is_updated_always' in item and
                    ax_field.is_updated_always != item['is_updated_always']):
                ax_field.is_updated_always = item['is_updated_always']
            if 'is_group' in item and ax_field.is_group != item['is_group']:
                ax_field.is_group = item['is_group']
            if ('is_always_whole_row' in item and
                    ax_field.is_always_whole_row
                    != item['is_always_whole_row']):
                ax_field.is_always_whole_row = item['is_always_whole_row']


def collect_ax_stats():
    """ Collect Ax usage statistics """
    with ax_model.scoped_session() as db_session:
        values = {}
        values['host'] = os.environ.get('AX_HOST', None)
        values['url'] = os.environ.get('AX_URL', None)
        values['dialect'] = os.environ.get('AX_DB_DIALECT', None)
        values['cache'] = os.environ.get('AX_CACHE_MODE', None)
        values['workersNum'] = os.environ.get('AX_SANIC_WORKERS', None)
        values['fingerprint'] = uuid.getnode()
        values['clientGuid'] = ax_auth.client_guid
        values['axVersion'] = os.environ.get('AX_VERSION', None)
        values['usersNum'] = db_session.query(AxUser).filter(
            AxUser.is_group.is_(False)).count()
        values['formsNum'] = db_session.query(AxForm).filter(
            AxForm.is_folder.is_(False)).count()
        # dbSize - #TODO how to do it?
        # sslUsed
        if os.environ.get('SSL_CERT_ABSOLUTE_PATH', None):
            values['sslUsed'] = True

        # actionCodeUsed
        if db_session.query(AxAction).filter(AxAction.code.isnot(None)).first():
            values['actionCodeUsed'] = True

        # gridCodeUsed
        if db_session.query(AxGrid).filter(AxGrid.code.isnot(None)).first():
            values['gridCodeUsed'] = True

        # roleCodeUsed
        if db_session.query(AxRole).filter(AxRole.code.isnot(None)).first():
            values['roleCodeUsed'] = True

        # adminEmails
        admin_emails = []
        admin_group = db_session.query(AxUser).filter(
            AxUser.is_admin.is_(True)
        ).filter(
            AxUser.is_group.is_(True)
        ).first()
        if admin_group:
            for usr in admin_group.users:
                if usr.email != 'default@ax-workflow.com':
                    admin_emails.append(usr.email)

        values['adminEmails'] = ", ".join(admin_emails)

        # fieldUsage
        # ax_fields = db_session.query(AxField.field_type_tag).filter(
        #     AxField.is_tab.is_(False)
        # ).all()
        # field_dict = {}
        # for fld in ax_fields:
        #     if fld.field_type_tag not in field_dict:
        #         field_dict[fld.field_type_tag] = 1
        #     else:
        #         field_dict[fld.field_type_tag] += 1
        # values['fieldUsage'] = field_dict
        this.stats = values


async def send_stats():
    """ Sends usage statistics to Ax sidekick server """
    # data = {
    #     "host": "hostHost",
    #     "usersNum": 10
    # }
    value_str = json.dumps(this.stats).replace('"', '\\"')
    query_str = (
        "    mutation{"
        "        doAction("
        "            formDbName: \"AxUsageStats\""
        "            actionDbName: \"newStats\""
        f"            values: \"{value_str}\""
        "        ) {"
        "            ok"
        "        }"
        "    }"
    )
    json_data = {'query': query_str}
    ret_str = await ax_misc.post_json(
        'http://ax-workflow.com/ax_stats', json_data, 5)
    return ret_str


def sync_field_types():
    """ Read field_types.yaml and check if any fields need to be
        created or modified """
    field_types_yaml = ax_misc.path('field_types.yaml')

    with ax_model.scoped_session() as db_session:

        ax_field_types = db_session.query(AxFieldType).all()
        existing_tags = []
        for field_type in ax_field_types:
            existing_tags.append(field_type.tag)

        if not os.path.isfile(field_types_yaml):
            raise FileNotFoundError('Configuration failed, field_types.yaml not found')

        with open(field_types_yaml, 'r') as stream:
            yaml_vars = yaml.safe_load(stream)
            for item in yaml_vars:
                if isinstance(item, dict) and 'tag' in item:
                    tag = item['tag']
                    if tag in existing_tags:
                        update_field_type(
                            field_types=ax_field_types, item=item)
                    else:
                        create_field_type(db_session=db_session, item=item)

            db_session.commit()


def database_fits_metadata() -> None:
    """Compare metada and database"""
    try:
        with ax_model.engine.connect() as active_connection:
            context = MigrationContext.configure(active_connection)
            db_session = ax_model.Session()
            ax_model.Base.query = db_session.query_property()
            metadata = ax_model.Base.metadata
            diff = compare_metadata(context, metadata)
            return diff == []
    except Exception:
        logger.exception('Error in comparing metadata and database.')
        raise


def upgrade_database():
    """Run Alembic migration script and update db version"""
    try:
        logger.info('Database does not fit metadata. Upgrading database.')
        command.upgrade(this.alembic_cfg, "head")
        command.stamp(this.alembic_cfg, "head")
    except Exception:
        logger.exception('Error upgrading database with Alembic')
        raise


def init_migration():
    """Initiate migration module"""
    init_alembic_config()
    if tables_exist() is False:
        create_tables()
        sync_field_types()
        # create_field_types()
        create_default_users()
        create_default_pages()
    else:
        sync_field_types()
        collect_ax_stats()
        try:
            asyncio.get_event_loop().run_until_complete(send_stats())
        except Exception:
            pass

        # if database_fits_metadata() is False:
        #     upgrade_database()
