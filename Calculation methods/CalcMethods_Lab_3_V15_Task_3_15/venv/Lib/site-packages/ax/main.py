"""Ax workflow apps builder.

Usage:
  ax [--host=<host>] [--port=<port>]
  ax --version
  ax --help

Options:
  -h --help       Show this screen.
  --version       Show version.
  --host=<host>   Host addres to run ax web application (default: 127.0.0.1).
  --port=<port>   Port of ax web application (default: 8080).

"""

import os
import sys
from pathlib import Path
from sanic import Sanic, response
from sanic_cors import CORS
from sanic_compress import Compress
from loguru import logger
from docopt import docopt

# fields specific
import stripe

# Add folder with main.py to sys.path.
root_path = Path(__file__).parent.resolve()
if root_path not in sys.path:
    sys.path.insert(0, str(root_path))


# pylint: disable=wrong-import-position
import backend.logger as ax_logger
import backend.misc as ax_misc
import backend.cache as ax_cache
import backend.model as ax_model
import backend.schema as ax_schema
import backend.pubsub as ax_pubsub
import backend.scheduler as ax_scheduler
import backend.migration as ax_migration
import backend.routes as ax_routes
import backend.dialects as ax_dialects
import backend.emails as ax_emails
import backend.auth as ax_auth

# pylint: enable=wrong-import-position


def init_model():
    """Initiate model. Used in alembic scripts"""
    ax_model.init_model(
        dialect=str(os.environ.get('AX_DB_DIALECT') or 'sqlite'),
        host=str(os.environ.get('AX_DB_HOST') or '127.0.0.1'),
        port=str(os.environ.get('AX_DB_PORT') or '5432'),
        login=str(os.environ.get('AX_DB_LOGIN') or ''),
        password=str(os.environ.get('AX_DB_PASSWORD') or ''),
        database=str(os.environ.get('AX_DB_DATABASE') or 'ax'),
        sqlite_filename=str(os.environ.get(
            'AX_DB_SQLITE_FILENAME') or 'ax_sqlite.db'),
        sqlite_absolute_path=os.environ.get(
            'AX_DB_SQLITE_ABSOLUTE_PATH') or None
    )


def init_fields():
    """ Initiate stripe. Used in AxPaymentStripe """
    if os.getenv('STRIPE_SECRET_KEY') and os.getenv('STRIPE_API_VERSION'):
        stripe.api_key = os.getenv('STRIPE_SECRET_KEY')
        stripe.api_version = os.getenv('STRIPE_API_VERSION')


def init_ax():
    """Initiate all modules of Ax"""

    # Load settings from app.yaml to os.environ
    ax_misc.load_configuration()
    # Misc functions used throw all application. Nothing specific.
    ax_misc.init_misc(
        timezone_name=str(os.environ.get('AX_TIMEZONE') or 'UTC'),
        tmp_absolute_path=os.environ.get('AX_TMP_ABSOLUTE_PATH') or None,
        uploads_absolute_path=os.environ.get(
            'AX_UPLOADS_ABSOLUTE_PATH') or None
    )
    # Logger (loguru) used in all modules - console + file + sentry
    ax_logger.init_logger(
        logs_filename=os.environ.get('AX_LOGS_FILENAME') or None,
        logs_absolute_path=os.environ.get('AX_LOGS_ABSOLUTE_PATH') or None,
        logs_level=os.environ.get('AX_LOGS_LEVEL') or 'INFO'
    )

    # for item, value in os.environ.items():
    #     logger.info('ENV: {}: {}'.format(item, value))

    # Initiate SqlAlchemy. Made with separate function for alembic.
    # It initiates database connection on migration.
    init_model()
    # Init cache module (aiocache). It is not yet used.
    ax_cache.init_cache(
        mode=str(os.environ.get('AX_CACHE_MODE') or 'default'),
        redis_endpoint=str(os.environ.get('AX_REDIS_ENDPOINT') or '127.0.0.1'),
        redis_port=int(os.environ.get('AX_REDIS_PORT') or 6379),
        redis_timeout=int(os.environ.get('AX_REDIS_TIMEOUT') or 1),
    )
    # Initiate pub-sub module. Used for web-socket subscriptions.
    # Notification on workflow action
    ax_pubsub.init_pubsub()
    # Check if database schema needs update
    ax_migration.init_migration()
    # Initiate gql schema.  Depends on cache and pubsub
    ax_schema.init_schema_standalone()

    # cors = CORS(app, resources={r"/api/*": {"origins": "*"}})
    CORS(app, automatic_options=True)  # TODO limit CORS to api folder

    # Enable gzip compression for responses
    # 'text/html','text/css','text/xml','application/json','application/java
    Compress(app)

    @app.listener('before_server_start')
    async def initialize_scheduler(_app, _loop):  # pylint: disable=unused-variable
        """Initiate scheduler. It used for cron-like jobs"""
        ax_scheduler.init_scheduler()

    @app.listener('before_server_start')
    def save_loop(_app, _loop):  # pylint: disable=unused-variable
        """Initiate graphene graphql server"""
        ax_routes.loop = _loop
        ax_routes.app = _app
        ax_routes.init_graphql_view()
        # _app.add_route(ax_routes.graphql_view, '/api/graphql')

    ssl_cert = os.environ.get('SSL_CERT_ABSOLUTE_PATH', None)
    ssl_key = os.environ.get('SSL_KEY_ABSOLUTE_PATH', None)
    ssl_enabled = False
    if ssl_cert and ssl_key:
        ssl_enabled = True

    if ssl_enabled:
        @app.middleware('request')
        async def force_ssl(request):     # pylint: disable=unused-variable
            if request.scheme == 'ws':
                return response.redirect(
                    request.url.replace('wss://', 'https://', 1),
                    status=301
                )
            elif request.scheme == 'http':
                return response.redirect(
                    request.url.replace('http://', 'https://', 1),
                    status=301
                )

    # Initiate all sanic server routes
    ax_routes.init_routes(
        sanic_app=app,
        pages_path=os.environ.get('AX_PAGES_ABSOLUTE_PATH'),
        ssl_enabled=ssl_enabled
    )
    # Initiate SQL dialects module. Different SQL queries for differents DBs
    ax_dialects.init_dialects(os.environ.get('AX_DB_DIALECT') or 'sqlite')

    # Initiate email sender
    ax_emails.init_email(
        smtp_host=os.environ.get('AX_SMTP_HOST'),
        smtp_login=os.environ.get('AX_SMTP_LOGIN'),
        smtp_password=os.environ.get('AX_SMTP_PASSWORD'),
        port=os.environ.get('AX_SMTP_PORT'),
        ssl=os.environ.get('AX_SMTP_SSL')
    )

    # Initiate auth module
    ax_auth.init_auth(
        sanic_app=app, secret=os.environ.get('AX_AUTH_SECRET'))

    init_fields()


ax_logo = """

                                           .
                                          .(
       ..                                 /(#
       ...           --- AX ---          ,/((////.
       ...,,                             ***(/////,
     ****,,,*/                          (****((///*
      ****///////                   ./(((#***/((/*,,,.
      ,/**////////((((/,      ,(((((((((/((**,.,..
        # (///((((((((((((#((((((((((////* ..
          # (((((((((((((##((((((((((((///,
             .#(((((((  ##(((((((((((((///
                       # (###/      /(///
                      # (//,
                      # (#            (//

"""


def main():
    """Main function"""
    arguments = docopt(__doc__)

    host = os.environ.get('AX_HOST', '127.0.0.1')
    port = int(os.environ.get('AX_PORT', 80))
    debug = bool(os.environ.get('AX_SANIC_DEBUG', False))
    access_log = bool(os.environ.get('AX_SANIC_ACCESS_LOG', False))
    workers = int(os.environ.get('AX_SANIC_WORKERS', 1))
    ssl_cert = os.environ.get('SSL_CERT_ABSOLUTE_PATH', None)
    ssl_key = os.environ.get('SSL_KEY_ABSOLUTE_PATH', None)

    if arguments['--host']:
        host = arguments['--host']

    if arguments['--port']:
        port = int(arguments['--port'])

    ssl = None
    protocol = 'http'
    if ssl_cert and ssl_key:
        ssl = {'cert': ssl_cert, 'key': ssl_key}
        protocol = 'https'

    print(ax_logo)
    logger.info(
        f'Ax is running with {workers} workers. Admin is avalible - {protocol}://{host}:{port}/admin/signin\n')
    app.run(
        host=host,
        port=port,
        debug=debug,
        access_log=access_log,
        workers=workers,
        ssl=ssl)


app = Sanic("Ax_workflow")
init_ax()

if __name__ == "__main__":
    main()
