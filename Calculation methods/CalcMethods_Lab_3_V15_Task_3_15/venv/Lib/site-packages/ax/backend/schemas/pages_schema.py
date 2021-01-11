"""This is part of GraphQL schema (Mutaions, Queryes, Subscriptions).
Defines AxPages Scheme and all mutations."""

import uuid
import graphene
from graphene_sqlalchemy.converter import convert_sqlalchemy_type
import markdown2

from backend.misc import convert_column_to_string
from backend.model import GUID, AxPage, AxPage2Users, AxUser, AxGroup2Users
from backend.auth import ax_admin_only
from backend.schemas.types import Page, PositionInput

import backend.model as ax_model
# import backend.cache as ax_cache
# import backend.dialects as ax_dialects

convert_sqlalchemy_type.register(GUID)(convert_column_to_string)


def apply_markdown(code):
    """ apply markdown to code """
    return markdown2.markdown(code)


def get_allowed_pages_guids(db_session, user_guid):
    """ Get all users and users groups, then get all pages guids that
        user can view """
    page_guids = []
    user_and_groups = []

    # Add everyone group
    everyone_group = db_session.query(AxUser).filter(
        AxUser.is_everyone.is_(True)
    ).first()
    if everyone_group:
        user_and_groups.append(everyone_group.guid)

    if user_guid:
        # Add current user
        user_and_groups.append(uuid.UUID(user_guid))

        # Add all-users group
        all_users_group = db_session.query(AxUser).filter(
            AxUser.is_all_users.is_(True)
        ).first()
        user_and_groups.append(all_users_group.guid)

        # Get user groups
        group2user_result = db_session.query(AxGroup2Users).filter(
            AxGroup2Users.user_guid == uuid.UUID(user_guid)
        ).all()
        for g2u in group2user_result:
            if g2u.group_guid not in user_and_groups:
                user_and_groups.append(g2u.group_guid)

    page2users_result = db_session.query(AxPage2Users).filter(
        AxPage2Users.user_guid.in_(user_and_groups)
    ).all()
    for p2u in page2users_result:
        if p2u.page_guid not in page_guids:
            page_guids.append(p2u.page_guid)

    return page_guids


class CreatePage(graphene.Mutation):
    """ Creates AxPage """
    class Arguments:  # pylint: disable=missing-docstring
        name = graphene.String()
        parent = graphene.String()

    ok = graphene.Boolean()
    page = graphene.Field(Page)

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = 'Error in gql mutation - pages_schema -> CreatePage.'
        with ax_model.try_catch(info.context['session'], err) as db_session:
            new_page = AxPage()
            new_page.name = args.get('name')
            new_page.parent = uuid.UUID(args.get('parent'))
            new_page.code = f"""<h1>{new_page.name}</h1>
Enter page content here"""
            db_session.add(new_page)
            db_session.flush()
            return CreatePage(page=new_page, ok=True)


class UpdatePage(graphene.Mutation):
    """ Update AxPage """
    class Arguments:  # pylint: disable=missing-docstring
        guid = graphene.String()
        name = graphene.String(required=False, default_value=None)
        db_name = graphene.String(required=False, default_value=None)
        code = graphene.String(required=False, default_value=None)
        parent = graphene.String(required=False, default_value=None)

    ok = graphene.Boolean()
    page = graphene.Field(Page)
    msg = graphene.String()

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        # avatar_tmp = args.get('avatar_tmp')
        guid = args.get('guid')
        name = args.get('name')
        db_name = args.get('db_name')
        code = args.get('code')
        parent = args.get('parent')

        err = 'Error in gql mutation - pages_schema -> UpdatePage.'
        with ax_model.try_catch(info.context['session'], err) as db_session:

            ax_page = db_session.query(AxPage).filter(
                AxPage.guid == uuid.UUID(guid)
            ).first()

            if name:
                ax_page.name = name

            if db_name:
                already_exist_page = db_session.query(AxPage).filter(
                    AxPage.db_name == db_name
                ).first()
                if already_exist_page:
                    return UpdatePage(
                        page=None, ok=False, msg='pages.db-name-exists')
                ax_page.db_name = db_name

            if code:
                ax_page.code = code

            if parent:
                ax_page.parent = uuid.UUID(parent)

            db_session.commit()
            ax_page.html = apply_markdown(ax_page.code)
            return UpdatePage(page=ax_page, ok=True, msg=None)


class DeletePage(graphene.Mutation):
    """ Deletes AxPage """
    class Arguments:  # pylint: disable=missing-docstring
        guid = graphene.String()

    ok = graphene.Boolean()
    deleted = graphene.String()

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = 'Error in gql mutation - pages_schema -> DeletePage.'
        with ax_model.try_catch(info.context['session'], err) as db_session:
            guid = args.get('guid')
            ax_page = db_session.query(AxPage).filter(
                AxPage.guid == uuid.UUID(guid)
            ).first()
            db_session.delete(ax_page)
            return DeletePage(deleted=guid, ok=True)


class AddUserToPage(graphene.Mutation):
    """ Creates AxPage2Users """
    class Arguments:  # pylint: disable=missing-docstring
        user_guid = graphene.String()
        page_guid = graphene.String()

    ok = graphene.Boolean()

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = 'Error in gql mutation - pages_schema -> AddUserToPage.'
        with ax_model.try_catch(info.context['session'], err) as db_session:
            user_guid = uuid.UUID(args.get('user_guid'))
            page_guid = uuid.UUID(args.get('page_guid'))

            page2user = db_session.query(AxPage2Users).filter(
                AxPage2Users.user_guid == user_guid
            ).filter(
                AxPage2Users.page_guid == page_guid
            ).first()
            if page2user:
                return AddUserToPage(ok=True)

            page2user = AxPage2Users()
            page2user.page_guid = page_guid
            page2user.user_guid = user_guid
            db_session.add(page2user)
            db_session.flush()

            return AddUserToPage(ok=True)


class RemoveUserFromPage(graphene.Mutation):
    """ Deletes AxPage2Users """
    class Arguments:  # pylint: disable=missing-docstring
        user_guid = graphene.String()
        page_guid = graphene.String()

    ok = graphene.Boolean()

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = 'Error in gql mutation - pages_schema -> RemoveUserFromPage.'
        with ax_model.try_catch(info.context['session'], err) as db_session:
            user_guid = uuid.UUID(args.get('user_guid'))
            page_guid = uuid.UUID(args.get('page_guid'))

            db_session.query(AxPage2Users).filter(
                AxPage2Users.user_guid == user_guid
            ).filter(
                AxPage2Users.page_guid == page_guid
            ).delete()
            db_session.flush()

            return RemoveUserFromPage(ok=True)


class ChangePagesPositions(graphene.Mutation):
    """Change position and parent of multiple pages"""
    class Arguments:  # pylint: disable=missing-docstring
        positions = graphene.List(PositionInput)

    ok = graphene.Boolean()
    pages = graphene.List(Page)

    @ax_admin_only
    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = "page_schema -> ChangePagesPositions"
        with ax_model.try_catch(info.context['session'], err) as db_session:
            positions = args.get('positions')
            for position in positions:
                db_page = db_session.query(AxPage).filter(
                    AxPage.guid == uuid.UUID(position.guid)
                ).one()
                current_parent = None
                if position.parent != '#':
                    current_parent = uuid.UUID(position.parent)
                db_page.parent = current_parent
                db_page.position = position.position

            db_session.flush()

            query = Page.get_query(info)  # SQLAlchemy query
            pages_list = query.all()
            return ChangePagesPositions(pages=pages_list, ok=True)


class PagesSubscription(graphene.ObjectType):
    """ Pages ws subscriptions """


class PagesQuery(graphene.ObjectType):
    """AxPage queryes"""
    all_pages = graphene.List(
        Page,
        update_time=graphene.Argument(type=graphene.String, required=False)
    )
    page_data = graphene.Field(
        Page,
        guid=graphene.Argument(type=graphene.String, required=False),
        update_time=graphene.Argument(type=graphene.String, required=False)
    )

    async def resolve_all_pages(self, info, update_time):
        """Get all pages"""
        del update_time
        current_user = info.context['user']
        err = 'Error in GQL query - resolve_all_pages.'
        with ax_model.try_catch(
                info.context['session'], err, no_commit=True) as db_session:

            user_guid = current_user.get(
                "user_id", None) if current_user else None
            user_is_admin = current_user.get(
                'is_admin', False) if current_user else False

            query = Page.get_query(info)  # SQLAlchemy query
            if user_is_admin:
                page_list = query.all()
                return page_list
            else:
                pages_guids = get_allowed_pages_guids(
                    db_session=db_session, user_guid=user_guid)
                page_list = query.filter(AxPage.guid.in_(pages_guids)).all()
                return page_list

    async def resolve_page_data(self, info, guid=None, update_time=None):
        """Get specific page"""
        del update_time
        current_user = info.context['user']
        user_is_admin = current_user.get(
            'is_admin', False) if current_user else False
        err = 'Error in GQL query - resolve_page_data.'
        with ax_model.try_catch(
                info.context['session'], err, no_commit=True) as db_session:
            user_guid = current_user.get(
                "user_id", None) if current_user else None
            query = Page.get_query(info)  # SQLAlchemy query
            page = None
            if guid:
                page = query.filter(AxPage.guid == uuid.UUID(guid)).first()
            else:
                page = query.filter(AxPage.parent.is_(None)).first()

            pages_guids = get_allowed_pages_guids(
                db_session=db_session, user_guid=user_guid)

            if page.guid in pages_guids or user_is_admin:
                page.html = apply_markdown(page.code)
                return page
            return None


class PagesMutations(graphene.ObjectType):
    """Contains all AxUser mutations"""
    create_page = CreatePage.Field()
    update_page = UpdatePage.Field()
    delete_page = DeletePage.Field()
    add_user_to_page = AddUserToPage.Field()
    remove_user_from_page = RemoveUserFromPage.Field()
    change_pages_positions = ChangePagesPositions.Field()
