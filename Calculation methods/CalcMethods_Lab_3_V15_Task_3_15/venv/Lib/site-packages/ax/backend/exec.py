""" Executes python code. Used in some field types, in dynamic roles """
# import os
import sys
# from loguru import logger
from dotmap import DotMap

import backend.dialects as ax_dialects
import backend.misc as ax_misc

this = sys.modules[__name__]


async def aexec(code, localz, **kwargs):
    """ This function wraps python code from AxAction with async function
    and runs it """
    # Restore globals later
    args = ", ".join(list(kwargs.keys()))
    code_from_action = code.replace("\n", "\n    ")
    async_code = (f"async def func({args}):"
                  f"\n    {code_from_action}"
                  f"\n    return ax")
    exec(async_code, {}, localz)    # pylint: disable=exec-used
    # Don't expect it to return from the coro.
    result = await localz["func"](**kwargs)
    return result


async def execute_field_code(code, form, arguments=None, current_user=None):
    """ Used to execute AxField backend code. see /backend/fields for info """
    localz = dict()
    host = await ax_misc.get_ax_host()
    ax = DotMap()  # javascript style dicts item['guid'] == item.guid
    ax.row.guid = form.row_guid
    ax.form = form
    ax.host = host
    ax.sql = ax_dialects.dialect.custom_query
    ax.user_email = None
    ax.user_guid = None
    if current_user:
        ax.user_email = current_user.get("email", None)
        ax.user_guid = current_user.get("user_id", None)
    for field in form.db_fields:
        ax.row[field.db_name] = field.value
    if arguments:
        for key, value in arguments.items():
            ax[key] = value
    localz['ax'] = ax

    try:
        await aexec(code=str(code), localz=localz, ax=ax)
        ret_ax = localz['ax']
        return ret_ax
    except SyntaxError as err:
        return err
    except Exception as err:    # pylint: disable=broad-except
        return err
