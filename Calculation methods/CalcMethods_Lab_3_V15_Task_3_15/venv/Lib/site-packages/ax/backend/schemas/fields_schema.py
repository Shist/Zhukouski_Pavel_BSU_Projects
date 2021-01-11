""" GQL queries used in fields. For now only AxMessages, AxApproval"""

import uuid
import json
import asyncio
import aiopubsub
import graphene
from loguru import logger
from sqlalchemy.orm import joinedload
import stripe

from backend.auth import ax_admin_only
from backend.model import AxMessage, AxMessageThread, AxForm, AxField
import backend.model as ax_model
import backend.misc as ax_misc
import backend.auth as ax_auth
import backend.pubsub as ax_pubsub

# import backend.emails as ax_emails
# import backend.cache as ax_cache
import backend.dialects as ax_dialects

from backend.schemas.types import Message, Field, RowInfo
# from backend.auth import ax_admin_only


class CreateMessage(graphene.Mutation):
    """ Creates AxMessage """
    class Arguments:  # pylint: disable=missing-docstring
        thread_guid = graphene.String()
        text = graphene.String()
        data_json = graphene.String(required=False, default_value=None)
        parent = graphene.String(required=False, default_value=None)

    ok = graphene.Boolean()
    message = graphene.Field(Message)

    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        err = 'Error in gql mutation - fields_schema -> CreateMessage.'
        with ax_model.try_catch(info.context['session'], err) as db_session:
            thread_guid = args.get('thread_guid')
            text = args.get('text')
            data_json = args.get('data_json')
            current_user = info.context['user']
            user_guid = current_user.get('user_id', None)
            user_email = current_user.get('email', None)
            parent = args.get('parent')

            data = None
            if data_json:
                try:
                    data = json.loads(data_json)
                except ValueError:
                    logger.exception(
                        'Error decoding data_json on creating AxMessage')

            thread = db_session.query(AxMessageThread).filter(
                AxMessageThread.guid == uuid.UUID(args.get('thread_guid'))
            ).first()
            if not thread:
                thread = AxMessageThread()
                thread.guid = uuid.UUID(thread_guid)
                db_session.add(thread)
                db_session.flush()

            new_message = AxMessage()
            new_message.author_guid = ax_misc.guid_or_none(user_guid)
            new_message.author_email = user_email
            new_message.text = text
            new_message.data_json = data
            new_message.thread_guid = thread.guid
            new_message.parent = ax_misc.guid_or_none(parent)

            db_session.add(new_message)
            db_session.flush()

            created_message = db_session.query(AxMessage).filter(
                AxMessage.guid == new_message.guid
            ).options(joinedload(AxMessage.author)).first()

            # joinedload(Event.user)

            db_session.expunge(created_message)
            db_session.expunge(created_message.author)
            ax_pubsub.publisher.publish(
                aiopubsub.Key('thread_message'), {
                    "thread_guid": str(created_message.thread_guid),
                    "ax_message": created_message
                })

            return CreateMessage(message=new_message, ok=True)


class GetStripeIntent(graphene.Mutation):
    """ Gets intent data from Stripe. Used to refresh payment status """
    class Arguments:  # pylint: disable=missing-docstring
        inten_id = graphene.String()

    ok = graphene.Boolean()
    intent = graphene.String()

    async def mutate(self, info, **args):  # pylint: disable=missing-docstring
        try:
            del info
            inten_id = args.get('inten_id')
            intent = stripe.PaymentIntent.retrieve(id=inten_id)
            intent_str = json.dumps(intent)

            ok = True
            return GetStripeIntent(intent=intent_str, ok=ok)
        except Exception:
            logger.exception('Error in gql mutation - GetStripeIntent.')
            raise


class FieldsSubscription(graphene.ObjectType):
    """GraphQL subscriptions"""

    thread_notify = graphene.Field(
        Message,
        thread_guid=graphene.Argument(type=graphene.String, required=True))

    async def resolve_thread_notify(self, info, thread_guid):
        """ Web-socket subscription on new messages in thread """
        try:
            del info
            subscriber = aiopubsub.Subscriber(
                ax_pubsub.hub, 'message_notify_subscriber')
            subscriber.subscribe(aiopubsub.Key('thread_message'))
            while True:
                key, payload = await subscriber.consume()
                await asyncio.sleep(0.1)
                del key
                if payload['thread_guid'] == thread_guid:
                    ax_message = payload['ax_message']
                    yield ax_message
        except asyncio.CancelledError:
            await subscriber.remove_all_listeners()
        except Exception:  # pylint: disable=broad-except
            logger.exception('Error in gql sub resolve_thread_notify.')


class FieldsQuery(graphene.ObjectType):
    """AxFields queryes"""
    thread_messages = graphene.List(
        Message,
        thread_guid=graphene.Argument(type=graphene.String),
        update_time=graphene.Argument(type=graphene.String, required=False)
    )
    to1_fields = graphene.List(
        Field,
        child_form_guid=graphene.Argument(type=graphene.String),
        field_guid=graphene.Argument(type=graphene.String),
        update_time=graphene.Argument(type=graphene.String, required=False)
    )

    to1_references = graphene.List(
        RowInfo,
        row_guid=graphene.Argument(type=graphene.String),
        field_guid=graphene.Argument(type=graphene.String),
        update_time=graphene.Argument(type=graphene.String, required=False)
    )

    async def resolve_thread_messages(
            self, info, thread_guid, update_time=None):
        """Get all AxMessages for specific thread. """
        del update_time
        err = 'Error in GQL query - resolve_thread_messages.'
        with ax_model.try_catch(info.context['session'], err) as db_session:
            current_user = info.context['user']

            if not thread_guid:
                return None

            # get thead
            thread = db_session.query(AxMessageThread).filter(
                AxMessageThread.guid == uuid.UUID(thread_guid)
            ).first()

            if not thread:
                return None

            # check field row permission
            perm = True
            if thread.field_guid and thread.row_guid:
                perm = await ax_auth.check_field_perm(
                    db_session=db_session,
                    current_user=current_user,
                    field_guid=thread.field_guid,
                    row_guid=thread.row_guid)

            if not perm:
                return None

            # get messages
            messages = thread.messages
            return messages

    @ax_admin_only
    async def resolve_to1_fields(
            self, info, child_form_guid, field_guid, update_time=None):
        """Get all AxMessages for specific thread. """
        del update_time
        err = 'Error in GQL query - resolve_to1_fields.'
        with ax_model.try_catch(info.context['session'], err) as db_session:

            ret_fields = []
            child_form = db_session.query(AxForm).filter(
                AxForm.guid == uuid.UUID(str(child_form_guid))
            ).first()

            current_field = db_session.query(AxField).filter(
                AxField.guid == uuid.UUID(str(field_guid))
            ).first()
            parent_form_db_name = str(current_field.form.db_name)

            for field in child_form.fields:
                if field.is_to1_field:
                    options = field.options
                    if options and options['form'] == parent_form_db_name:
                        db_session.expunge(field)
                        ret_fields.append(field)

            return ret_fields

    async def resolve_to1_references(
            self, info, field_guid, row_guid, update_time=None):
        """ Used in Ax1to1Children. Selects all 1to1 references to parent row
        """
        del update_time
        err = 'Error in GQL query - resolve_to1_fields.'
        with ax_model.try_catch(info.context['session'], err) as db_session:

            # Check if user have access to field

            ret_guids = []
            parent_field = db_session.query(AxField).filter(
                AxField.guid == uuid.UUID(str(field_guid))
            ).first()

            if parent_field.options and parent_field.options['field']:
                child_form_db_name = parent_field.options['form']

                child_field_guid = parent_field.options['field']
                child_field = db_session.query(AxField).filter(
                    AxField.guid == uuid.UUID(str(child_field_guid))
                ).first()

            result = await ax_dialects.dialect.select_to1_children(
                db_session=db_session,
                child_form_db_name=child_form_db_name,
                child_field_db_name=child_field.db_name,
                parent_row_guid=row_guid)

            if result:
                for row in result:
                    ret_guids.append(RowInfo(guid=row['guid']))

            return ret_guids


class FieldsMutations(graphene.ObjectType):
    """Contains all mutations"""
    create_message = CreateMessage.Field()
    get_stripe_intent = GetStripeIntent.Field()
