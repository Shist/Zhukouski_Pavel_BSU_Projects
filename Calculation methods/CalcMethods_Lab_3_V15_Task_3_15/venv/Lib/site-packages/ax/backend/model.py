"""Axy Class Model
Contains class structure of Ax storage.
"""

import os
import re
import sys
from pathlib import Path
from datetime import datetime
from contextlib import contextmanager
import uuid
import json
from loguru import logger
from sqlalchemy import create_engine
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, relationship
from sqlalchemy import Text, String, CHAR, Float, Unicode, Boolean, Integer,\
    TIMESTAMP, JSON
from sqlalchemy import TypeDecorator, Column, LargeBinary
from sqlalchemy import ForeignKey
from sqlalchemy.dialects.postgresql import UUID
# from sqlalchemy.pool import SingletonThreadPool

import backend.misc as ax_misc

this = sys.modules[__name__]
engine = None
# db_session = None
db_url = None
Base = declarative_base()
Session = None  # pylint: disable=invalid-name


@contextmanager
def scoped_session(error_msg=None):
    """ Using the scoped_session contextmanager is
     best practice to ensure the session gets closed
     and reduces noise in code by not having to manually
     commit or rollback the db if a exception occurs.
     Example - with ax_model.scoped_session(msg) as db_session:
     """
    session = this.Session()
    try:
        yield session
        session.commit()
    except:
        if error_msg:
            logger.exception(f'scoped_sesion -> {error_msg}')
        session.rollback()
        raise
    finally:
        session.close()


@contextmanager
def try_catch(db_session, error_msg=None, no_commit=False):
    """ Catches database errors and rollsback session
    with ax_model.try_catch(info.context['session'], err) as db_session: """
    try:
        yield db_session
        if not no_commit:
            db_session.commit()
    except:
        if error_msg:
            logger.exception(f'{error_msg}')
        db_session.rollback()
        raise


def init_model(dialect: str, host: str, port: str, login: str, password: str,
               database: str, sqlite_filename: str, sqlite_absolute_path: str
               ) -> None:
    """Initiate database model

    Args:
        dialect (str): Supported dialects: sqlite | mysql
        host (str): Database host
        port (str): Database port
        login (str): Database user
        password (str): Database user password
        database (str): Database schema name
        sqlite_filename (str): Sqlite database file name. (ax_sqlite.db)
        sqlite_absolute_path (str): Path to Sqlite file. If file does not exist
            it will be created
    """
    try:
        if dialect == 'sqlite':
            if sqlite_absolute_path is None:
                db_path = ax_misc.path(sqlite_filename)
                this.db_url = 'sqlite:///' + str(db_path)
            else:
                db_path = str(Path(sqlite_absolute_path) / sqlite_filename)
                this.db_url = 'sqlite:///' + db_path

            logger.debug('DB url = {url}', url=this.db_url)
            # print(f'DB url = {this.db_url}')
            this.engine = create_engine(
                this.db_url,
                pool_threadlocal=True,
                connect_args={'timeout': 10})
            # TODO take sql timeout from app.yaml
        elif dialect == 'postgre':
            this.db_url = (
                f'postgresql+pypostgresql://{login}:{password}@{host}:{port}/{database}')

            logger.debug('DB url = {url}', url=this.db_url)
            this.engine = create_engine(
                this.db_url,
                convert_unicode=True,
                pool_size=30,
                pool_use_lifo=True,
                max_overflow=0,
                pool_recycle=3600,
                pool_pre_ping=True,
                connect_args={'connect_timeout': 10})
        else:
            msg = 'This database dialect is not supported'
            logger.error(msg)
            raise Exception(msg)

        this.Session = sessionmaker(bind=this.engine)

        # poolclass=SingletonThreadPool,
        # this.db_session = scoped_session(sessionmaker(autocommit=False,
        #                                               autoflush=False,
        #                                               bind=this.engine))
        # this.Base.query = db_session.query_property()

    except Exception:
        logger.exception('Error initating SqlAlchemy model')
        raise


class GUID(TypeDecorator):  # pylint: disable=W0223
    """Platform-independent GUID type.

    Uses PostgreSQL's UUID type, otherwise uses
    CHAR(32), storing as stringified hex values.

    """
    impl = CHAR

    def load_dialect_impl(self, dialect):
        if dialect.name == 'postgresql':
            return dialect.type_descriptor(UUID())
        else:
            return dialect.type_descriptor(CHAR(32))

    def process_bind_param(self, value, dialect):
        if value is None:
            return value
        elif dialect.name == 'postgresql':
            return str(value)
        else:
            if not isinstance(value, uuid.UUID):
                return str(uuid.UUID(value))
                # return "%.32x" % uuid.UUID(value).int
            else:
                return str(value)
                # return "%.32x" % value.int

    def process_result_value(self, value, dialect):
        if value is None:
            return value
        else:
            if not isinstance(value, uuid.UUID):
                value = uuid.UUID(value)
            return value


class AxAlembicVersion(Base):
    """Stores current Database version for alembic migration"""
    __tablename__ = '_ax_alembic_version'
    version_num = Column(String(255), primary_key=True)


class AxMetric(Base):
    """Stores varius key/values.
    1 - counters for AxNum field"""
    __tablename__ = '_ax_metrics'
    guid = Column(GUID(), primary_key=True,
                  default=uuid.uuid4, unique=True, nullable=False)
    key = Column(String(255), unique=True, nullable=False)
    value = Column(String(255))


class AxSchedulerJob(Base):
    """Table and metadata for apscheduler."""
    __tablename__ = '_ax_scheduler_jobs'
    id = Column(Unicode(191, _warn_on_bytestring=False), primary_key=True)
    next_run_time = Column(Float(25), index=True)
    job_state = Column(LargeBinary, nullable=False)


class AxForm(Base):
    """Stores Ax-Forms"""
    __tablename__ = '_ax_forms'
    guid = Column(GUID(), primary_key=True,
                  default=uuid.uuid4, unique=True, nullable=False)
    name = Column(String(255))
    db_name = Column(String(255))   # Must be PascalCase. It is used to create
    # database tables and graphql schema
    parent = Column(GUID())  # Parent form. Used for visual tree in AdminHome
    position = Column(Integer())  # Position in tree
    fields = relationship(
        "AxField", order_by="AxField.position", cascade="all, delete-orphan")
    grids = relationship("AxGrid", order_by="AxGrid.position")
    states = relationship("AxState", cascade="all, delete-orphan")
    actions = relationship("AxAction", cascade="all, delete-orphan")
    roles = relationship("AxRole", cascade="all, delete-orphan")
    tom_label = Column(String(255))  # Used for displaying rows in relation
    # fields. {{name}} will result in
    # displaying name field as form chip
    icon = Column(String(255))  # font-awesome key
    is_folder = Column(Boolean, unique=False, default=False)  # Used in tree
    row_guid = None  # Stores current row guid.
    current_state_name = ""
    current_state_object = None
    from_state_name = ""
    from_state_object = None
    avalible_actions = None
    modal_guid = None   # Used in web-socket subscriptions to determin if
    # currrent form needs to notify on action
    permissions = relationship(
        "AxRoleFieldPermission", cascade="all, delete-orphan")

    @property
    def db_fields(self):
        """Only AxFields that are database columns"""
        db_fields = []
        for field in self.fields:
            if field.is_tab is False and not field.field_type.is_virtual:
                db_fields.append(field)
        return db_fields

    @property
    def no_tab_fields(self):
        """Only AxFields that are database columns"""
        db_fields = []
        for field in self.fields:
            if field.is_tab is False:
                db_fields.append(field)
        return db_fields

    @property
    def perm_states(self):
        """Only AxStates that have perms - all without deleted and all"""
        states = []
        for state in self.states:
            if state.is_all is False and state.is_deleted is False:
                states.append(state)
        return states

    def get_row_data(self):
        """Set current AxForm to match specific row in database table"""
        return "GET ROW DATA"

    def get_field(self, field_db_name):
        """ returns AxFiled by given db_name of field"""
        for field in self.fields:
            if field.db_name == field_db_name:
                return field
        return None


class AxFieldType(Base):
    """List of avalible ax field types"""
    __tablename__ = '_ax_field_types'
    # Same as vue component. Like AxNum, AxString
    tag = Column(String(64), primary_key=True, unique=True)
    name = Column(String(255))
    parent = Column(String(64))  # Used in tree. Parent is always group.
    position = Column(Integer())  # Used in tree.
    default_name = Column(String(255))  # Comes from locale
    default_db_name = Column(String(255))
    # TEXT/INY/DECIMAL... Used by dialect.py
    value_type = Column(String(255))
    # to determin how to store current field
    comparator = Column(String(255))    # string/number Used in AxGrid to know
    # how to sort current fields columns

    icon = Column(String(255))  # font-awesome key
    is_group = Column(Boolean, unique=False,
                      default=False)  # Used in types tree
    # virtual meens that field is calculated, not stored in database
    # DB column is not created
    is_virtual = Column(Boolean, unique=False, default=False)
    virtual_source = Column(String(255))
    # readonly meens that field is set by backend or action.
    # DB column is created but data does not come from form.
    is_readonly = Column(Boolean, unique=False, default=False)
    # True if field type have custom ag-grid column and have inline edit
    is_inline_editable = Column(Boolean, unique=False, default=False)
    # True if field have backend python code. Wich is executed before/after
    # insert/update/delete. Check backend/fields/ for more info
    is_backend_available = Column(Boolean, unique=False, default=False)
    # True if field type have custom ag-grid column
    is_columnn_avalible = Column(Boolean, unique=False, default=False)
    # True meens that this field is updated even if was not modified in form.
    # from/after backend code of field is executed on every action
    # Example - Changelog must be updated always, on every action
    is_updated_always = Column(Boolean, unique=False, default=False)
    # True meens that current field type always must be displayed as whole row
    is_always_whole_row = Column(Boolean, unique=False, default=False)
    # True if fields type have python code that must be executed before form
    # is displayed. Check backend/fields/AxHtml for more info
    is_display_backend_avalible = Column(Boolean, unique=False, default=False)

    def __init__(self,
                 tag, name=None,
                 position=0,
                 default_name=None,
                 default_db_name="",
                 value_type="",
                 parent="",
                 icon="",
                 comparator="",
                 virtual_source=None,
                 is_virtual=False,
                 is_readonly=False,
                 is_inline_editable=False,
                 is_backend_available=False,
                 is_display_backend_avalible=False,
                 is_columnn_avalible=False,
                 is_updated_always=False,
                 is_group=False,
                 is_always_whole_row=False
                 ):
        self.tag = tag
        self.name = name
        self.position = position
        self.default_name = default_name
        self.default_db_name = default_db_name
        self.value_type = value_type
        self.parent = parent
        self.is_group = is_group
        self.comparator = comparator
        self.icon = icon
        self.virtual_source = virtual_source
        self.is_virtual = is_virtual
        self.is_readonly = is_readonly
        self.is_inline_editable = is_inline_editable
        self.is_backend_available = is_backend_available
        self.is_display_backend_avalible = is_display_backend_avalible
        self.is_columnn_avalible = is_columnn_avalible
        self.is_updated_always = is_updated_always
        self.is_always_whole_row = is_always_whole_row


class AxField(Base):
    """List of fields in each form"""
    __tablename__ = '_ax_fields'
    guid = Column(GUID(), primary_key=True,
                  default=uuid.uuid4, unique=True, nullable=False)
    form_guid = Column(GUID(), ForeignKey('_ax_forms.guid'))
    form = relationship("AxForm")
    name = Column(String(255))
    db_name = Column(String(255))   # Must be camelCase. It used to create
    # database table columns and GQL fields
    position = Column(Integer())  # tree position
    options_json = Column(JSON())  # Stores JSON with params used by Vue
    # component. It is passed to UI
    # Stores JSON that is used only in python actions. AxAction code or fields
    # before/after methods
    private_options_json = Column(JSON())
    # TODO - delete this line!! - Column(Text(convert_unicode=True))
    field_type_tag = Column(String(64), ForeignKey('_ax_field_types.tag'))
    field_type = relationship("AxFieldType")
    # True if current field is form tab
    is_tab = Column(Boolean, unique=False, default=False)
    is_required = Column(Boolean, unique=False, default=False)
    is_whole_row = Column(Boolean, unique=False, default=False)
    parent = Column(GUID())  # Tab guid
    value = None
    is_hidden = False
    is_readonly = False
    needs_sql_update = False  # Flag that current field must be updated in DB
    force_sql_update = False  # Flag that current field must be updated in DB
    # Works even if field is hidden or read_only

    @property
    def is_virtual(self):
        """Is current fieldtype is Virtual (calculated field)"""
        if self.field_type.is_virtual:
            return True
        return False

    @property
    def options(self):
        """ return parsed options_json """
        return json.loads(self.options_json)

    @property
    def files_path(self):
        """ returns path to directory where files for
        current field would be stored """
        files_path = os.path.join(
            ax_misc.uploads_root_dir,
            'form_row_field_file',
            str(self.form.guid),
            str(uuid.UUID(str(self.form.row_guid))),
            str(str(self.guid))
        )
        return files_path

    @property
    def is_relation_field(self):
        """Check is field is of realtion type """
        if self.field_type and self.field_type.tag in ['Ax1to1', 'Ax1tom', 'Ax1tomTable']:
            return True
        return False

    @property
    def is_to1_field(self):
        """Check is field is of realtion type """
        if self.field_type and self.field_type.tag == 'Ax1to1':
            return True
        return False

    @property
    def is_tom_field(self):
        """Check is field is of realtion type """
        if self.field_type and self.field_type.tag in ['Ax1tom', 'Ax1tomTable']:
            return True
        return False


class AxGrid(Base):
    """Stores Ax grids"""
    __tablename__ = '_ax_grids'
    guid = Column(GUID(), primary_key=True,
                  default=uuid.uuid4, unique=True, nullable=False)
    name = Column(String(255))
    # Must be PascalCase, used in GQL schema Types
    db_name = Column(String(255))
    position = Column(Integer())    # Position in tree
    options_json = Column(JSON())  # JSON key/value see
    # TheConstructorGridsDrawerSecond.vue
    code = Column(Text(convert_unicode=True))  # code to build SQL query
    # Columns widths stored here too
    form_guid = Column(GUID(), ForeignKey('_ax_forms.guid'))
    form = relationship("AxForm")
    is_default_view = Column(Boolean)
    columns = relationship(
        "AxColumn", order_by="AxColumn.position", cascade="all, delete-orphan")


class AxColumn(Base):
    """Stores columns for each grid"""
    __tablename__ = '_ax_columns'
    guid = Column(GUID(), primary_key=True,
                  default=uuid.uuid4, unique=True, nullable=False)
    position = Column(Integer())    # Position in grid and in tree
    options_json = Column(JSON())  # Currently not used
    field_guid = Column(GUID(), ForeignKey('_ax_fields.guid'))
    field = relationship("AxField")
    grid_guid = Column(GUID(), ForeignKey('_ax_grids.guid'))
    grid = relationship("AxGrid")
    column_type = Column(String(50))  # Not used. Was used for aggregate grid
    aggregation_type = Column(String(50), nullable=True)  # Not used yet.


class AxGroup2Users(Base):
    """Stores info on groups and users relation. What users are in group X."""
    __tablename__ = '_ax_group2user'
    guid = Column(GUID(), primary_key=True,
                  default=uuid.uuid4, unique=True, nullable=False)
    group_guid = Column(GUID(), ForeignKey('_ax_users.guid'))
    user_guid = Column(GUID(), ForeignKey('_ax_users.guid'))


class AxUser(Base):
    """Describes Ax users."""
    __tablename__ = '_ax_users'
    guid = Column(GUID(), primary_key=True,
                  default=uuid.uuid4, unique=True, nullable=False)
    name = Column(String(255))
    short_name = Column(String(255))
    info = Column(Text(convert_unicode=True))
    email = Column(String(255))
    password = Column(String(255))
    password_must_change = Column(Boolean, unique=False, default=False)
    is_group = Column(Boolean, unique=False, default=False)
    is_admin = Column(Boolean, unique=False, default=False)
    is_everyone = Column(Boolean, unique=False, default=False)
    is_all_users = Column(Boolean, unique=False, default=False)
    is_email_confirmed = Column(Boolean, unique=False, default=False)
    parent = Column(GUID())
    avatar = Column(LargeBinary)
    position = Column(Integer)
    is_blocked = Column(Boolean, unique=False, default=False)
    users = relationship(
        "AxUser",
        secondary='_ax_group2user',
        primaryjoin="AxUser.guid==AxGroup2Users.group_guid",
        secondaryjoin="AxUser.guid==AxGroup2Users.user_guid",
        backref="users_in_group"
    )
    is_active_admin = False

    def to_dict(self):
        """ Required for sanic-jwt """
        return {"user_id": str(self.guid), "short_name": self.short_name}


class AxRole2Users(Base):
    """What users and groups are assigned to Role?"""
    __tablename__ = '_ax_role2user'
    guid = Column(GUID(), primary_key=True,
                  default=uuid.uuid4, unique=True, nullable=False)
    role_guid = Column(GUID(), ForeignKey('_ax_roles.guid'))
    user_guid = Column(GUID(), ForeignKey('_ax_users.guid'))


class AxRole(Base):
    """Stores Roles for each workflow"""
    __tablename__ = '_ax_roles'
    guid = Column(GUID(), primary_key=True,
                  default=uuid.uuid4, unique=True, nullable=False)
    name = Column(String(255))
    form_guid = Column(GUID(), ForeignKey('_ax_forms.guid'))
    form = relationship("AxForm")
    users = relationship("AxUser", secondary='_ax_role2user')
    icon = Column(String(255))  # font-awesome key
    # field_tag = Column(String(255))
    is_dynamic = Column(Boolean, unique=False, default=False)
    code = Column(Text(convert_unicode=True))  # code to build SQL query

    @property
    def db_name(self):
        """ Removes every character but letters and numbers from name """
        return re.sub(r'[\W_]+', '', self.name)


class AxState2Role(Base):
    """Stores Roles that are assigned for state of workflow"""
    __tablename__ = '_ax_state2role'
    guid = Column(GUID(), primary_key=True,
                  default=uuid.uuid4, unique=True, nullable=False)
    state_guid = Column(GUID(), ForeignKey('_ax_states.guid'))
    role_guid = Column(GUID(), ForeignKey('_ax_roles.guid'))


class AxState(Base):
    """Stores states for each workflow"""
    __tablename__ = '_ax_states'
    guid = Column(GUID(), primary_key=True,
                  default=uuid.uuid4, unique=True, nullable=False)
    name = Column(String(255))
    form_guid = Column(GUID(), ForeignKey('_ax_forms.guid'))
    form = relationship("AxForm")
    roles = relationship("AxRole", secondary='_ax_state2role')
    is_start = Column(Boolean, unique=False, default=False)
    is_deleted = Column(Boolean, unique=False, default=False)
    is_all = Column(Boolean, unique=False, default=False)
    x = Column(Float)
    y = Column(Float)


class AxAction2Role(Base):
    """What roles are assigned for each action of workflow"""
    __tablename__ = '_ax_action2role'
    guid = Column(GUID(), primary_key=True,
                  default=uuid.uuid4, unique=True, nullable=False)
    action_guid = Column(GUID(), ForeignKey('_ax_actions.guid'))
    role_guid = Column(GUID(), ForeignKey('_ax_roles.guid'))


class AxAction(Base):
    """Stores actions for each workflow"""
    __tablename__ = '_ax_actions'
    guid = Column(GUID(), primary_key=True,
                  default=uuid.uuid4, unique=True, nullable=False)
    name = Column(String(255))
    db_name = Column(String(255))
    form_guid = Column(GUID(), ForeignKey('_ax_forms.guid'))
    form = relationship("AxForm")
    roles = relationship("AxRole", secondary='_ax_action2role')
    from_state_guid = Column(GUID(), ForeignKey('_ax_states.guid'))
    to_state_guid = Column(GUID(), ForeignKey('_ax_states.guid'))
    from_state = relationship('AxState', foreign_keys=[from_state_guid])
    to_state = relationship('AxState', foreign_keys=[to_state_guid])
    # Python code that is executed on this action. Sea action_schema.py
    code = Column(Text(convert_unicode=True))
    # If not None, the user will be see prompt before action is executed
    confirm_text = Column(String(255))
    # If True, the form will be closed after this action
    close_modal = Column(Boolean, unique=False, default=True)
    icon = Column(String(255))  # font-awesome key
    radius = Column(Float)  # used in d3 worklfow constructor
    messages = None  # Used to store messages and exceptions got from code
    # Execution


class AxRoleFieldPermission(Base):
    """What role can view fields on each state of workflow"""
    __tablename__ = '_ax_role_field_permissions'
    guid = Column(GUID(), primary_key=True,
                  default=uuid.uuid4, unique=True, nullable=False)
    form_guid = Column(GUID(), ForeignKey('_ax_forms.guid'))
    form = relationship("AxForm")
    role_guid = Column(GUID(), ForeignKey('_ax_roles.guid'))
    role = relationship("AxRole")
    state_guid = Column(GUID(), ForeignKey('_ax_states.guid'))
    state = relationship("AxState")
    field_guid = Column(GUID(), ForeignKey('_ax_fields.guid'))
    field = relationship("AxField")
    read = Column(Boolean, unique=False, default=False)
    edit = Column(Boolean, unique=False, default=False)


class Ax1tomReference(Base):
    """Stores 1 to M fields relation"""
    __tablename__ = '_ax_mtom_references'
    guid = Column(GUID(), primary_key=True,
                  default=uuid.uuid4, unique=True, nullable=False)
    form_guid = Column(GUID(), ForeignKey('_ax_forms.guid'))
    field_guid = Column(GUID(), ForeignKey('_ax_fields.guid'))
    row_guid = Column(GUID())
    child_guid = Column(GUID())


class AxPage(Base):
    """ Stores all pages """
    __tablename__ = '_ax_pages'
    guid = Column(GUID(), primary_key=True,
                  default=uuid.uuid4, unique=True, nullable=False)
    name = Column(String(255))
    db_name = Column(String(255))
    code = Column(Text(convert_unicode=True))
    options_json = Column(JSON())
    parent = Column(GUID())
    position = Column(Integer())  # Position in tree
    html = None


class AxPage2Users(Base):
    """What users and groups can view what pages?"""
    __tablename__ = '_ax_page2user'
    guid = Column(GUID(), primary_key=True,
                  default=uuid.uuid4, unique=True, nullable=False)
    page_guid = Column(GUID(), ForeignKey('_ax_pages.guid'))
    user_guid = Column(GUID(), ForeignKey('_ax_users.guid'))


class AxMessage(Base):
    """ Messages used in AxMessages, AxApproval """
    __tablename__ = '_ax_messages'
    guid = Column(GUID(), primary_key=True,
                  default=uuid.uuid4, unique=True, nullable=False)
    created = Column(TIMESTAMP(), default=datetime.utcnow, nullable=False)
    edited = Column(TIMESTAMP())
    author_guid = Column(GUID(), ForeignKey('_ax_users.guid'))
    author = relationship('AxUser')
    text = Column(Text(convert_unicode=True))
    data_json = Column(JSON())
    thread_guid = Column(GUID(), ForeignKey('_ax_message_threads.guid'))
    # thread = relationship('AxMessageThread')


class AxMessageThread(Base):
    """ Used to roup AxMessages and get permissions """
    __tablename__ = '_ax_message_threads'
    guid = Column(GUID(), primary_key=True,
                  default=uuid.uuid4, unique=True, nullable=False)
    parent = Column(GUID())  # Not used for now. Can be used for threads
    field_guid = Column(GUID(), ForeignKey('_ax_fields.guid'))
    field = relationship('AxField')
    row_guid = Column(GUID())
    code_name = Column(String(255))
    messages = relationship("AxMessage")
