"""Module with aiocache instance. Works inMemory or with redis
"""

import sys
from aiocache import caches
from loguru import logger

this = sys.modules[__name__]
cache = None


def init_cache(
        mode: str,
        redis_endpoint: str,
        redis_port: int,
        redis_timeout: int) -> bool:
    """Initiate aiocache cache.

    Args:
        mode (str, optional): Defaults to 'default'. Set 'redis' for Redis.
        redis_endpoint (str, optional): Defaults to '127.0.0.1'. IP of Redis.
        redis_port (int, optional): Defaults to 6379. Port of Redies server.
        redis_timeout (int, optional): Defaults to 1. Redis timeout.

    Returns:
        bool: True if succesuful
    """

    aiocache_config = {
        'default': {
            'cache': "aiocache.SimpleMemoryCache",
            'serializer': {
                'class': "aiocache.serializers.PickleSerializer"
            }
        },
        'redis': {
            'cache': "aiocache.RedisCache",
            'endpoint': redis_endpoint,
            'port': redis_port,
            'timeout': redis_timeout,
            'serializer': {
                'class': "aiocache.serializers.PickleSerializer"
            },
            'plugins': [
                {'class': "aiocache.plugins.HitMissRatioPlugin"},
                {'class': "aiocache.plugins.TimingPlugin"}
            ]
        }
    }

    caches.set_config(aiocache_config)
    if mode == 'redis':
        try:
            this.cache = caches.get('redis')
            logger.info(f'Using redis for cache - [{redis_endpoint}]')
        except Exception:
            logger.exception('Error initiating aiocache with Redis.')
            raise
    else:
        try:
            this.cache = caches.get('default')
            logger.info(f'Using RAM for cache')
        except Exception:
            logger.exception(
                'Error initiating aiocache with SimpleMemoryCache. ')
            raise

    return True
