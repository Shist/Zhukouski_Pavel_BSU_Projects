""" Local fork of sanic_graphql lib """

import re
import time
from collections import Mapping
from functools import partial
from cgi import parse_header


from promise import Promise
from sanic.response import HTTPResponse
from sanic.views import HTTPMethodView
from sanic_jwt.decorators import inject_user

from graphql.type.schema import GraphQLSchema
from graphql.execution.executors.asyncio import AsyncioExecutor
from graphql_server import (HttpQueryError, default_format_error,
                            encode_execution_results, json_encode,
                            load_json_body, run_http_query)

from loguru import logger
import backend.model as ax_model
import backend.auth as ax_auth
import backend.schema as ax_schema


start_time = None


def log_reguest(request, time=None):
    """ Logs graphql reuests """
    request_type = 'query'
    type_match = re.search('^(.*?) ', request.json['query'])
    if type_match:
        request_type = type_match.group(0)
    names_match = re.findall('([a-zA-Z].+?)\(', request.json['query'])

    if not names_match:
        # query without params
        without_match = re.findall('(.[a-zA-Z]+?) *?{', request.json['query'])
        command_names = without_match[0] + '...'
    else:
        clear_match = []
        for name in names_match:
            if 'query' not in name and 'mutation' not in name:
                clear_match.append(name)
        command_names = ', '.join(clear_match)

    # msg = request.json['query']
    msg = f'{request_type} -> {command_names}'
    # if time:
    #     msg += f' : {time}'

    logger.debug(msg)


class GraphQLView(HTTPMethodView):
    """ Local fork of sanic_graphql lib """

    decorators = [inject_user(), ax_auth.ax_protected()]

    schema = None
    executor = None
    root_value = None
    context = None
    pretty = False
    graphiql = False
    graphiql_version = None
    graphiql_template = None
    middleware = None
    batch = False
    jinja_env = None
    max_age = 86400

    _enable_async = True

    methods = ['GET', 'POST', 'PUT', 'DELETE']

    def __init__(self, **kwargs):
        """ Initiate """
        super(GraphQLView, self).__init__()
        for key, value in kwargs.items():
            if hasattr(self, key):
                setattr(self, key, value)

        self._enable_async = self._enable_async and isinstance(
            self.executor, AsyncioExecutor)
        assert isinstance(
            self.schema, GraphQLSchema), 'A Schema is required'

    # noinspection PyUnusedLocal

    def get_root_value(self, request):  # pylint: disable=unused-argument
        """ Some getter """
        return self.root_value

    def get_context(self, request):
        """ Returns saved context. Contains reqest, db_session, user """
        context = (
            self.context.copy()
            if self.context and
            isinstance(self.context, Mapping)
            else {}
        )
        if isinstance(context, Mapping) and 'request' not in context:
            context.update({'request': request})

        # log_reguest(request)
        # logger.debug(request.json['query'])

        return context

    def get_middleware(self, request):  # pylint: disable=unused-argument
        """ Some getter """
        return self.middleware

    def get_executor(self, request):  # pylint: disable=unused-argument
        """ Some getter """
        return self.executor

    format_error = staticmethod(default_format_error)
    encode = staticmethod(json_encode)

    async def dispatch_request(self, request, *args, **kwargs):
        """ Sanic view request dispatch.  """
        start_time = time.time()  # TODO this is debug profile

        with ax_model.scoped_session("GQL error -") as db_session:
            try:
                request_method = request.method.lower()
                data = self.parse_body(request)

                show_graphiql = request_method == 'get' and self.should_display_graphiql(
                    request)
                catch = show_graphiql

                pretty = self.pretty or show_graphiql or request.args.get(
                    'pretty')

                user = kwargs['user'] or None

                # auth_header = request.headers['authorization']
                # print(auth_header)

                ax_context = self.get_context(request)
                ax_context.update({'session': db_session})
                ax_context.update({'user': user})

                if request_method != 'options':
                    execution_results, all_params = run_http_query(
                        ax_schema.schema,
                        request_method,
                        data,
                        query_data=request.args,
                        batch_enabled=self.batch,
                        catch=catch,

                        # Execute options
                        return_promise=self._enable_async,
                        root_value=self.get_root_value(request),
                        context_value=ax_context,
                        middleware=self.get_middleware(request),
                        executor=self.get_executor(request),
                    )  # pylint: disable=unused-argument
                    del all_params
                    awaited_execution_results = await Promise.all(
                        execution_results)
                    result, status_code = encode_execution_results(
                        awaited_execution_results,
                        is_batch=isinstance(data, list),
                        format_error=self.format_error,
                        encode=partial(self.encode, pretty=pretty)
                    )
                    log_reguest(request, (time.time() - start_time))

                    return HTTPResponse(
                        result,
                        status=status_code,
                        content_type='application/json'
                    )
                else:
                    log_reguest(request, (time.time() - start_time))
                    return self.process_preflight(request)

            except HttpQueryError as err:
                logger.exception(f'graqlView -> {err}')
                return HTTPResponse(
                    self.encode({
                        'errors': [default_format_error(err)]
                    }),
                    status=err.status_code,
                    headers=err.headers,
                    content_type='application/json'
                )
            except Exception as err:    # pylint: disable=broad-except
                logger.exception(f'graqlView -> {err}')

    # noinspection PyBroadException

    def parse_body(self, request):
        """ - """
        content_type = self.get_mime_type(request)
        if content_type == 'application/graphql':
            return {'query': request.body.decode('utf8')}

        elif content_type == 'application/json':
            return load_json_body(request.body.decode('utf8'))

        elif content_type in (
                'application/x-www-form-urlencoded', 'multipart/form-data'):
            return request.form

        return {}

    @staticmethod
    def get_mime_type(request):
        """ - """
        # We use mimetype here since we don't need the other
        # information provided by content_type
        if 'content-type' not in request.headers:
            return None

        mimetype, _ = parse_header(request.headers['content-type'])
        return mimetype

    def should_display_graphiql(self, request):
        """ - """
        if not self.graphiql or 'raw' in request.args:
            return False

        return self.request_wants_html(request)

    def request_wants_html(self, request):
        """ - """
        accept = request.headers.get('accept', {})
        return 'text/html' in accept or '*/*' in accept

    def process_preflight(self, request):
        """ Preflight request support for apollo-client
        https://www.w3.org/TR/cors/#resource-preflight-requests """
        origin = request.headers.get('Origin', '')
        method = request.headers.get(
            'Access-Control-Request-Method', '').upper()

        if method and method in self.methods:
            return HTTPResponse(
                status=200,
                headers={
                    'Access-Control-Allow-Origin': origin,
                    'Access-Control-Allow-Methods': ', '.join(self.methods),
                    'Access-Control-Max-Age': str(self.max_age),
                }
            )
        else:
            return HTTPResponse(
                status=400,
            )
