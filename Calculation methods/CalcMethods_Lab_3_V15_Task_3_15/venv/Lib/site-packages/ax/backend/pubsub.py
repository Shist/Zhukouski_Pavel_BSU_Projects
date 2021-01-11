"""Pubsub module. Google aiopubsub for move info """

import sys
import aiopubsub
from loguru import logger

this = sys.modules[__name__]
hub = None
publisher = None


def init_pubsub():
    """Initiate pubsub module, create default publisher"""
    try:
        this.hub = aiopubsub.Hub()
        this.publisher = aiopubsub.Publisher(
            this.hub, prefix=aiopubsub.Key())
    except Exception:
        logger.exception('Error initiationg pubsub module')
        raise
