"""AxPaymentStripe

For AxPaymentStripe to work you need to create intent in AxAction python
code like so  (stripe1)-

    ax.row.stripe['intent'] = ax.stripe.PaymentIntent.create(
        amount=500,
        currency='usd',
    )

WARNING! Amount must be multipleed by 100! amount=500 meens 5$

4242424242424242	Succeeds and immediately processes the payment.
4000002500003155	Requires authentication.
                    Stripe will trigger a modal asking for
                    the customer to authenticate.
4000000000009995	Always fails with a decline code of insufficient_funds.

"""
import os


async def before_insert(db_session, field, before_form, tobe_form, action,
                        current_user):
    """ Create default value of field.  """
    del db_session, before_form, tobe_form, action, current_user
    field.value = {
        "pubKey": os.getenv('STRIPE_PUBLISHABLE_KEY'),
        "intent": None
    }
    field.force_sql_update = True
    return field.value
