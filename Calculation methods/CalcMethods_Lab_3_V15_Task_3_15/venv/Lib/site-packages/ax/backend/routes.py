"""All routes of ax-core and ax-admin"""

import os
import sys
import asyncio
import uuid
import json
from sanic import response
from loguru import logger
from graphql.execution.executors.asyncio import AsyncioExecutor
from graphql_ws.websockets_lib import WsLibSubscriptionServer
from sanic_jwt.decorators import inject_user
import markdown2

from backend.graphqlview import GraphQLView
import backend.cache as ax_cache
import backend.schema as ax_schema
import backend.misc as ax_misc
from backend.tus import tus_bp
import backend.model as ax_model
from backend.model import AxForm, AxField
import backend.schemas.form_schema as form_schema
import backend.dialects as ax_dialects
import backend.auth as ax_auth
import backend.migration as ax_migration
from backend.auth import ax_protected


this = sys.modules[__name__]

loop = asyncio.new_event_loop()
actions_loop = asyncio.new_event_loop()
app = None
graphql_view = None


def init_graphql_view():  # pylint: disable=unused-variable
    """Initiate graphql"""
    this.graphql_view = GraphQLView.as_view(
        schema=ax_schema.schema,
        graphiql=False,
        enable_async=True,
        executor=AsyncioExecutor(loop=this.loop)
    )
    this.app.add_route(this.graphql_view, '/api/graphql')


def init_routes(sanic_app, pages_path=None, ssl_enabled=False):  # pylint: disable=unused-variable
    """Innitiate all Ax routes"""
    del ssl_enabled
    try:
        sanic_app.static('/uploads', str(ax_misc.path('uploads')))
        sanic_app.static('/static', str(ax_misc.path('dist/ax/static')))
        sanic_app.static('/stats', str(ax_misc.path('dist/ax/stats.html')))
        sanic_app.static(
            '/test_webpack', str(ax_misc.path('dist/ax/test.html')))

        sanic_app.static(
            '/editor.worker.js', str(ax_misc.path('dist/ax/editor.worker.js')))
        sanic_app.static(
            '/html.worker.js', str(ax_misc.path('dist/ax/html.worker.js')))
        sanic_app.static(
            'json.worker.js', str(ax_misc.path('dist/ax/json.worker.js')))

        # Pages routes {
        pages_dist_path = str(ax_misc.path('dist/pages'))
        if pages_path:
            pages_dist_path = pages_path
        index_path = str(os.path.join(pages_dist_path, "index.html"))

        sanic_app.static(
            '/pages/static', str(ax_misc.path('dist/pages/static')))
        # TODO WTF this guid? maybe must be part of build?

        pre_cache_file_name = None
        pages_dist_dir = ax_misc.path('dist/pages')
        file_list = os.listdir(pages_dist_dir)
        for name in file_list:
            if "precache-manifest." in name:
                pre_cache_file_name = name

        sanic_app.static(
            f'/pages/{pre_cache_file_name}',
            str(ax_misc.path(f'dist/pages/{pre_cache_file_name}')))     # pylint: disable=line-too-long
        sanic_app.static(
            '/pages/service-worker.js',
            str(ax_misc.path('dist/pages/service-worker.js')))
        sanic_app.static(
            '/pages/manifest.json',
            str(ax_misc.path('dist/pages/manifest.json')))
        sanic_app.static(
            '/pages/robots.txt',
            str(ax_misc.path('dist/pages/robots.txt')))

        sanic_app.static('/pages', index_path)

        @sanic_app.route('/pages/<path:path>')
        def pages_index(request, path=None):  # pylint: disable=unused-variable
            """  """
            del request, path
            return response.html(open(index_path).read())

        @sanic_app.route('/signin')
        def pages_index1(request, path=None):  # pylint: disable=unused-variable
            """  """
            del request, path
            return response.html(open(index_path).read())

        # Pages routes }

        # Add tus upload blueprint
        sanic_app.blueprint(tus_bp)
        # Add web-socket subscription server
        subscription_server = WsLibSubscriptionServer(ax_schema.schema)

        @sanic_app.route('api/signout', methods=['GET'])
        @inject_user()
        @ax_protected()
        async def signout(request, user=None):   # pylint: disable=unused-variable
            """ Delete all auth cookies and redirect to signin """

            user_guid = user.get('user_id', None) if user else None
            if user_guid:
                key = f'refresh_token_{user_guid}'
                await ax_cache.cache.delete(key)

            to_url = '/signin'
            if request.args.get('to_admin', False):
                to_url = '/admin/signin'

            resp = response.redirect(to_url)
            del resp.cookies['ax_auth']
            del resp.cookies['access_token']
            del resp.cookies['refresh_token']
            return resp

        @sanic_app.route(
            '/api/file/<form_guid>/<row_guid>/<field_guid>/<file_name>',
            methods=['GET'])
        @inject_user()
        @ax_protected()
        async def db_file_viewer(   # pylint: disable=unused-variable
                request, form_guid, row_guid, field_guid, file_name, user):  # pylint: disable=unused-variable
            """ Used to display files that are stored in database.
                Used in fields like AxImageCropDb"""
            current_user = user
            del request, form_guid, file_name
            with ax_model.scoped_session("routes.db_file_viewer") as db_session:
                safe_row_guid = str(uuid.UUID(str(row_guid)))
                ax_field = db_session.query(AxField).filter(
                    AxField.guid == uuid.UUID(field_guid)
                ).first()

                # first we select only guid and axState to know, if user have
                # access
                row_result = await ax_dialects.dialect.select_one(
                    db_session=db_session,
                    form=ax_field.form,
                    fields_list=[],
                    row_guid=safe_row_guid)

                state_name = row_result[0]['axState']
                state_guid = await ax_auth.get_state_guid(
                    ax_form=ax_field.form,
                    state_name=state_name)

                user_guid = current_user.get(
                    'user_id', None) if current_user else None
                user_is_admin = current_user.get(
                    'is_admin', False) if current_user else False
                allowed_field_dict = await ax_auth.get_allowed_fields_dict(
                    ax_form=ax_field.form,
                    user_guid=user_guid,
                    state_guid=state_guid)

                field_guid = str(ax_field.guid)
                if not user_is_admin:
                    if (field_guid not in allowed_field_dict or
                            allowed_field_dict[field_guid] == 0 or
                            allowed_field_dict[field_guid] is None):
                        email = current_user.get('email', None)
                        msg = (
                            f'Error in db_file_viewer. ',
                            f'not allowed for user [{email}]'
                        )
                        logger.error(msg)
                        return response.text("", status=403)

                field_value = await ax_dialects.dialect.select_field(
                    db_session=db_session,
                    form_db_name=ax_field.form.db_name,
                    field_db_name=ax_field.db_name,
                    row_guid=safe_row_guid)

                return response.raw(
                    field_value, content_type='application/octet-stream')

        @sanic_app.route(
            '/api/file/<form_guid>/<row_guid>/<field_guid>/<file_guid>/<file_name>',    # pylint: disable=line-too-long
            methods=['GET'])
        @inject_user()
        @ax_protected()
        async def file_viewer(  # pylint: disable=unused-variable
                request, form_guid, row_guid, field_guid, file_guid, file_name,\
                user=None):
            """ Used to display files uploaded and stored on disk.
                Displays temp files too. Used in all fields with upload"""
            del request
            current_user = user
            with ax_model.scoped_session("routes -> file_viewer") as db_session:
                # if row_guid is null -> display from /tmp without permissions
                if not row_guid or row_guid == 'null':
                    tmp_dir = os.path.join(ax_misc.tmp_root_dir, file_guid)
                    file_name = os.listdir(tmp_dir)[0]
                    temp_path = os.path.join(tmp_dir, file_name)
                    return await response.file(temp_path)

                # get AxForm with row values
                ax_form = db_session.query(AxForm).filter(
                    AxForm.guid == uuid.UUID(form_guid)
                ).first()
                ax_form = await form_schema.set_form_values(
                    db_session=db_session,
                    ax_form=ax_form,
                    row_guid=row_guid,
                    current_user=current_user)

                # Get values from row, field
                field_values = None
                for field in ax_form.fields:
                    if field.guid == uuid.UUID(field_guid):
                        if field.value:
                            field_values = json.loads(field.value)

                # Find requested file in value
                the_file = None
                for file in field_values:
                    if file['guid'] == file_guid:
                        the_file = file

                if not the_file:
                    return response.text("", status=404)

                state_guid = await ax_auth.get_state_guid(
                    ax_form=ax_form,
                    state_name=ax_form.current_state_name)

                user_guid = current_user.get(
                    'user_id', None) if current_user else None
                user_is_admin = current_user.get(
                    'is_admin', False) if current_user else False
                allowed_field_dict = await ax_auth.get_allowed_fields_dict(
                    ax_form=ax_form,
                    user_guid=user_guid,
                    state_guid=state_guid)

                if not user_is_admin:
                    if (field_guid not in allowed_field_dict or
                            allowed_field_dict[field_guid] == 0 or
                            allowed_field_dict[field_guid] is None):
                        email = current_user['email']
                        msg = (
                            f'Error in file_viewer. ',
                            f'not allowed for user [{email}]'
                        )
                        logger.error(msg)
                        return response.text("", status=403)

                # if file exists -> return file
                row_guid_str = str(uuid.UUID(row_guid))
                file_path = os.path.join(
                    ax_misc.uploads_root_dir,
                    'form_row_field_file',
                    form_guid,
                    row_guid_str,
                    field_guid,
                    the_file['guid'],
                    the_file['name'])
                if not os.path.lexists(file_path):
                    return response.text("", status=404)
                return await response.file(file_path)

        @sanic_app.route('/admin/<path:path>')
        def index(request, path=None):  # pylint: disable=unused-variable
            """ This is MAIN ROUTE. (except other routes listed in this module).
                All requests are directed to Vue single page app. After that Vue
                handles routing."""
            del request, path
            absolute_path = ax_misc.path('dist/ax/index.html')
            return response.html(open(absolute_path).read())

        @sanic_app.route('/form/<path:path>')
        def index1(request, path=None):  # pylint: disable=unused-variable
            """ Copy of index. Sanic bug - https://github.com/huge-success/sanic/pull/1779"""
            del request, path
            absolute_path = ax_misc.path('dist/ax/index.html')
            return response.html(open(absolute_path).read())

        @sanic_app.route('/grid/<path:path>')
        def index2(request, path=None):  # pylint: disable=unused-variable
            """ Copy of index. Sanic bug - https://github.com/huge-success/sanic/pull/1779"""
            del request, path
            absolute_path = ax_misc.path('dist/ax/index.html')
            return response.html(open(absolute_path).read())

        @sanic_app.route('/admin/signin')
        def index3(request, path=None):  # pylint: disable=unused-variable
            """ Copy of index. Sanic bug - https://github.com/huge-success/sanic/pull/1779"""
            del request, path
            absolute_path = ax_misc.path('dist/ax/index.html')
            return response.html(open(absolute_path).read())

        @sanic_app.route('/')
        def handle_request(request):  # pylint: disable=unused-variable
            del request
            return response.redirect('/pages')

        @sanic_app.route('/api/draw_ax')
        async def draw_ax(request):  # pylint: disable=unused-variable
            """ Outputs bundle.js. Used when Ax web-components
                are inputed somewhere. Users can use this url for <script> tag
                """
            del request
            absolute_path = ax_misc.path('dist/ax/static/js/ax-bundle.js')
            return await response.file(
                absolute_path,
                headers={
                    'Content-Type': 'application/javascript; charset=utf-8'
                }
            )

        @sanic_app.route('/draw_ax')
        async def draw_ax1(request):  # pylint: disable=unused-variable
            """ Outputs bundle.js. Used when Ax web-components
                are inputed somewhere. Users can use this url for <script> tag
                """
            del request
            absolute_path = ax_misc.path('dist/ax/static/js/ax-bundle.js')
            return await response.file(
                absolute_path,
                headers={
                    'Content-Type': 'application/javascript; charset=utf-8'
                }
            )

        @sanic_app.websocket('/api/subscriptions', subprotocols=['graphql-ws'])
        async def subscriptions(request, web_socket):  # pylint: disable=unused-variable
            """Web socket route for graphql subscriptions"""
            del request
            try:
                # TODO: Why socket error exception occurs without internet
                await subscription_server.handle(web_socket)
                return web_socket
            except asyncio.CancelledError:
                pass
                # logger.exception('Socket error')

        @sanic_app.route('/api/ping')
        async def ping(request):  # pylint: disable=unused-variable
            """ Ping function checks if Ax is running. Used with monit """
            del request
            from backend.schema import schema
            result = schema.execute("query { ping }")
            test_str = json.dumps(result.data, sort_keys=True, indent=4)
            return response.text(test_str)

        @sanic_app.route('/api/blog_rss')
        async def blog_rss(request):  # pylint: disable=unused-variable
            """ Fetches medium blog rss """
            del request
            feed = await ax_misc.fetch('https://medium.com/feed/@enf644')   # pylint: disable=line-too-long
            return response.text(feed)

        @sanic_app.route('/api/stackoverflow_rss')
        async def stackoverflow_rss(request):  # pylint: disable=unused-variable
            """ Fetches stackoverflow tag rss """
            del request
            feed = await ax_misc.fetch('https://stackexchange.com/feeds/tagsets/381786/ax-workflow?sort=active')   # pylint: disable=line-too-long
            return response.text(feed)

        @sanic_app.route('/api/home_welcome')
        async def home_welcome(request):  # pylint: disable=unused-variable
            """ Fetches welcome_free.md from ax-info """
            del request
            the_url = 'https://raw.githubusercontent.com/enf644/ax-info/master/welcome_free.md'
            if ax_auth.lise_is_active():
                the_url = 'https://raw.githubusercontent.com/enf644/ax-info/master/welcome.md'
            feed = await ax_misc.fetch(the_url)   # pylint: disable=line-too-long
            html = markdown2.markdown(feed)
            return response.text(html)

        @sanic_app.route('/api/marketplace_featured')
        async def marketplace_featured(request):  # pylint: disable=unused-variable
            """ Fetches featured apps json """
            del request
            feed = await ax_misc.fetch('https://raw.githubusercontent.com/enf644/ax-info/master/featured_apps.json')   # pylint: disable=line-too-long
            return response.text(feed)

        @sanic_app.route('/api/marketplace_all')
        async def marketplace_apps(request):  # pylint: disable=unused-variable
            """ Fetches all apps json """
            del request
            feed = await ax_misc.fetch('https://raw.githubusercontent.com/enf644/ax-info/master/apps.json')   # pylint: disable=line-too-long
            return response.text(feed)

        @sanic_app.route('/api/test')
        async def test(request):  # pylint: disable=unused-variable
            """Test function"""
            del request

            ret_str = await ax_migration.send_stats()

            # data = {
            #     "host": "hostHost",
            #     "usersNum": 10
            # }
            # value_str = json.dumps(data).replace('"', '\\"')
            # query_str = (
            #     "    mutation{"
            #     "        doAction("
            #     "            formDbName: \"AxUsageStats\""
            #     "            actionDbName: \"newStats\""
            #     f"            values: \"{value_str}\""
            #     "        ) {"
            #     "            ok"
            #     "        }"
            #     "    }"
            # )

            # json_data = {'query': query_str}
            # ret_str = await ax_misc.post_json(
            #     'http://127.0.0.1:8080/api/graphql', json_data)

            # ret_str = ax_model.engine.pool.status()
            # this.test_schema = 'IT WORKS'
            # ax_pubsub.publisher.publish(
            #     aiopubsub.Key('dummy_test'), this.test_schema)
            return response.text(ret_str)

        @sanic_app.route('/api/set')
        async def cache_set(request):  # pylint: disable=unused-variable
            """Cache Test function"""
            del request
            obj = ['one', 'two', 'three']
            await ax_cache.cache.set('user_list', obj)
            return response.text('Cache SET' + str(obj))

        @sanic_app.route('/api/get')
        async def cache_get(request):  # pylint: disable=unused-variable
            """Cache Test function"""
            del request
            obj = await ax_cache.cache.get('user_list')
            ret_str = 'READ cache == ' + \
                str(obj[0].username + ' - ' + os.environ['AX_VERSION'])
            return response.text(ret_str)

    except Exception:
        logger.exception('Error initiating routes.')
        raise
