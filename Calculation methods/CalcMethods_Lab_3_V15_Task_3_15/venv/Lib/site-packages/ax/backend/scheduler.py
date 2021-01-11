"""Scheduler using APScheduller
1 - Test scheduler Job - 5 sec after sanic start
2 - Clean /tmp folder - every 30 mins
"""
import os
import sys
import time
import shutil
import asyncio
from datetime import timedelta, datetime
from apscheduler.schedulers.asyncio import AsyncIOScheduler
from apscheduler.executors.asyncio import AsyncIOExecutor
from apscheduler.jobstores.sqlalchemy import SQLAlchemyJobStore
# from graphql.execution.executors.asyncio import AsyncioExecutor
from loguru import logger
import backend.model as ax_model
import backend.misc as ax_misc

this = sys.modules[__name__]
scheduler = None


async def prn_job(message):
    """ Executed aftrer sanic app start to know if scheduler is working"""
    print(str(message))
    return False


async def clear_tmp_files():
    """ Delete all files from /tmp folder wich is expired """
    tmp_folder = ax_misc.tmp_root_dir
    for root, dirs, _ in os.walk(tmp_folder):
        del root
        for dir_name in dirs:
            dir_to_check = os.path.join(tmp_folder, dir_name)
            seconds = time.time() - os.path.getmtime(dir_to_check)
            minutes = int(seconds) / 60
            if minutes > 120:   # 120 minutes expiration time
                shutil.rmtree(dir_to_check)


async def gql_query_job(query, variables):
    """ Jon that executes Graphql query """
    from backend.schema import schema
    # result = schema.execute(query, variables=variables)

    await schema.execute(
        query,
        variables=variables,
        return_promise=True)
#         executor=AsyncioExecutor(loop=asyncio.get_event_loop()),


# def do_action_REM(form_db_name, action_db_name, values, row_guid=None):
#     """
#     Adds job that executes GQL query for workflow action. Used in AxAction
#     python code.

#     Args:
#         form_db_name (str): db_name of AxForm
#         action_db_name (str): db_name of AxAction that needs to be performed
#         values (Dict): Dict with form values. Keys are db table columns
#         row_guid (str): Guid (not dashes) of database row

#     """

#     query = f"""
#         mutation(
#             $formDbName: String,
#             $actionDbName: String,
#             $rowGuid: String,
#             $values: String
#         ){{
#             doAction(
#                 formDbName: $formDbName
#                 actionDbName: $actionDbName
#                 rowGuid: $rowGuid
#                 values: $values
#             ) {{
#                 form {{
#                 guid
#                 dbName
#                 }}
#                 newGuid
#                 messages
#                 ok
#             }}
#         }}
#     """
#     variables = {
#         "formDbName": form_db_name,
#         "actionDbName": action_db_name,
#         "rowGuid": row_guid,
#         "values": json.dumps(values)
#     }
#     args = {
#         "query": query,
#         "variables": variables
#     }
#     job = this.scheduler.add_job(func=gql_query_job, kwargs=args,
#                                  misfire_grace_time=60 * 60)
#     print(str(job))


def add_action_job(form_db_name, action_db_name, values, row_guid=None,
                   wait_seconds=0):
    """ Adds scheduller job that executes a AxAction """
    import backend.schemas.action_schema as ax_action_schema
    variables = {
        "form_db_name": form_db_name,
        "action_db_name": action_db_name,
        "row_guid": row_guid,
        "values": values
    }
    moscow_dt = datetime.now() + timedelta(seconds=wait_seconds)

    job = this.scheduler.add_job(
        func=ax_action_schema.execute_action,
        kwargs=variables,
        misfire_grace_time=60 * 60,
        trigger='date',
        next_run_time=moscow_dt)
    print(str(job))


def init_scheduler():
    """Initiate scheduller"""
    # https://apscheduler.readthedocs.io/en/latest/modules/schedulers/base.html#apscheduler.schedulers.base.BaseScheduler.add_job

    # TODO UTC must match timezone from config
    try:
        jobstores = {
            'default': SQLAlchemyJobStore(
                engine=ax_model.engine,
                tablename='_ax_scheduler_jobs'
            )
        }

        executors = {
            'default': AsyncIOExecutor()
        }

        loop = asyncio.get_event_loop()
        this.scheduler = AsyncIOScheduler(
            jobstores=jobstores,
            executors=executors,
            timezone=ax_misc.timezone,
            event_loop=loop)
        this.scheduler.start()

        # Job cleaning /uploads/tmp folder. deletes files that are expired
        all_jobs = this.scheduler.get_jobs()
        if "clear_tmp_files" not in [job.name for job in all_jobs]:
            this.scheduler.add_job(
                clear_tmp_files,
                trigger='cron',
                minute='30',
                coalesce=True,
                misfire_grace_time=60,
                id='clear_tmp_files')

        if "prn_job" not in [job.name for job in all_jobs]:
            now_dt = ax_misc.date() + timedelta(seconds=5)
            this.scheduler.add_job(
                prn_job,
                'date',
                run_date=now_dt,
                args=['SCHEDULER WORKS'],
                id='prn_job',
                misfire_grace_time=60
            )

    except Exception:
        logger.exception('Error initiating scheduler module. ')
        raise
