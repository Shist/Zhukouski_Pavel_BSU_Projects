""" Describes all static GraphQL types
Create GQL type for each SqlAlchemy model. All SqlAlchemy columns are created by
graphene. But if we need additional params, we need to discribe them.
Example - AxForm have row_guid param wich is not Column. To use this param
in GQL query we must discribe row_guid again in Form type.

"""
from sqlalchemy import JSON
import graphene
from graphene import relay
from graphene_sqlalchemy import SQLAlchemyObjectType
from graphene_sqlalchemy.converter import convert_sqlalchemy_type
from backend.model import AxForm, AxField, AxFieldType, AxGrid, AxColumn, \
    AxUser, AxGroup2Users, AxRole, AxState, AxAction, AxAction2Role, \
    AxState2Role, AxRoleFieldPermission, AxRole2Users, GUID, AxPage, \
    AxPage2Users, AxMessage
from backend.misc import convert_column_to_string

convert_sqlalchemy_type.register(GUID)(convert_column_to_string)
convert_sqlalchemy_type.register(JSON)(convert_column_to_string)


class Action(SQLAlchemyObjectType):  # pylint: disable=missing-docstring
    class Meta:  # pylint: disable=missing-docstring
        model = AxAction
        interfaces = (relay.Node, )


class Form(SQLAlchemyObjectType):  # pylint: disable=missing-docstring
    class Meta:  # pylint: disable=missing-docstring
        model = AxForm
        interfaces = (relay.Node, )
    row_guid = graphene.String()
    modal_guid = graphene.String()
    avalible_actions = graphene.List(Action)


class FieldType(SQLAlchemyObjectType):  # pylint: disable=missing-docstring
    class Meta:  # pylint: disable=missing-docstring
        model = AxFieldType
        interfaces = (relay.Node, )


class PositionInput(graphene.InputObjectType):
    """Used to store position data"""
    guid = graphene.NonNull(graphene.String)
    position = graphene.NonNull(graphene.Int)
    parent = graphene.NonNull(graphene.String)


class ConsoleMessage(graphene.ObjectType):
    """ - """
    modal_guid = graphene.String()
    text = graphene.String()


class RowInfo(graphene.ObjectType):
    """ Used in Ax1to1Children. """
    guid = graphene.String()
    state = graphene.String()
    tom_label = graphene.String()


class ActionNotifyMessage(graphene.ObjectType):
    """ - """
    form_guid = graphene.String()
    form_icon = graphene.String()
    form_db_name = graphene.String()
    row_guid = graphene.String()
    modal_guid = graphene.String()
    action_guid = graphene.String()
    action_db_name = graphene.String()
    action_icon = graphene.String()


class Field(SQLAlchemyObjectType):  # pylint: disable=missing-docstring
    class Meta:  # pylint: disable=missing-docstring
        model = AxField
        interfaces = (relay.Node, )
    value = graphene.String()
    is_hidden = graphene.Boolean()
    is_readonly = graphene.Boolean()


class Grid(SQLAlchemyObjectType):  # pylint: disable=missing-docstring
    class Meta:  # pylint: disable=missing-docstring
        model = AxGrid
        interfaces = (relay.Node, )
    code_not_none = graphene.String()


class Column(SQLAlchemyObjectType):  # pylint: disable=missing-docstring
    class Meta:  # pylint: disable=missing-docstring
        model = AxColumn
        interfaces = (relay.Node, )


class User(SQLAlchemyObjectType):  # pylint: disable=missing-docstring
    class Meta:  # pylint: disable=missing-docstring
        model = AxUser
        interfaces = (relay.Node, )
        exclude_fields = ('avatar', 'password')
    is_active_admin = graphene.Boolean()


class Role(SQLAlchemyObjectType):  # pylint: disable=missing-docstring
    class Meta:  # pylint: disable=missing-docstring
        model = AxRole
        interfaces = (relay.Node, )


class State(SQLAlchemyObjectType):  # pylint: disable=missing-docstring
    class Meta:  # pylint: disable=missing-docstring
        model = AxState
        interfaces = (relay.Node, )


class RoleFieldPermission(SQLAlchemyObjectType):  # pylint: disable=missing-docstring
    class Meta:  # pylint: disable=missing-docstring
        model = AxRoleFieldPermission
        interfaces = (relay.Node, )


class Group2Users(SQLAlchemyObjectType):  # pylint: disable=missing-docstring
    class Meta:  # pylint: disable=missing-docstring
        model = AxGroup2Users
        interfaces = (relay.Node, )


class Action2Role(SQLAlchemyObjectType):  # pylint: disable=missing-docstring
    class Meta:  # pylint: disable=missing-docstring
        model = AxAction2Role
        interfaces = (relay.Node, )


class State2Role(SQLAlchemyObjectType):  # pylint: disable=missing-docstring
    class Meta:  # pylint: disable=missing-docstring
        model = AxState2Role
        interfaces = (relay.Node, )


class Role2Users(SQLAlchemyObjectType):  # pylint: disable=missing-docstring
    class Meta:  # pylint: disable=missing-docstring
        model = AxRole2Users
        interfaces = (relay.Node, )


class Page(SQLAlchemyObjectType):  # pylint: disable=missing-docstring
    class Meta:  # pylint: disable=missing-docstring
        model = AxPage
        interfaces = (relay.Node, )
    html = graphene.String()


class Page2Users(SQLAlchemyObjectType):  # pylint: disable=missing-docstring
    class Meta:  # pylint: disable=missing-docstring
        model = AxPage2Users
        interfaces = (relay.Node, )


class Message(SQLAlchemyObjectType):  # pylint: disable=missing-docstring
    class Meta:  # pylint: disable=missing-docstring
        model = AxMessage
        interfaces = (relay.Node, )


class LicenseInfo(graphene.ObjectType):  # pylint: disable=missing-docstring
    client_guid = graphene.String()
    max_users = graphene.String()
