"""Initiate loguru"""
import sys
from pathlib import Path
from loguru import logger
import backend.misc as ax_misc


def init_logger(logs_filename: str, logs_absolute_path: str, logs_level: str):
    """Initiate loguru

    Args:
        logs_filename (str): Desired name of log file. If None, only console is
            used.
        logs_absolute_path (str): Path where log file must be created. If None -
            the /backend/logs folder will be used
        logs_level (str): What log level to use INFO/ERROR/DEBUG. Default ERROR
    """
    # sys.stdout.reconfigure(encoding='utf-8')
    # sys.stdout.reconfigure(errors='backslashreplace')

    config = {
        "handlers": [
            {
                'sink': sys.stdout,
                'colorize': True,
                'format': 'Ax  | {level} | <level>{message}</level>',
                'backtrace': False,
                'level': logs_level
            }
        ],
        "extra": {"user": "someone"}
    }

# ⛏️

    try:
        # If log_filename set in app.yaml, then we must write log file
        if logs_filename is not None:
            log_path = ax_misc.path('backend/logs/' + logs_filename)
            if logs_absolute_path is not None:
                log_path = str(Path(logs_absolute_path) / logs_filename)

            # TODO add rotation and retention, compression from app.yaml
            file_handler = {
                'sink': log_path,
                'serialize': True,
                'rotation': '100 MB',
                'enqueue': True,
                'backtrace': False,
                'level': logs_level
            }
            config['handlers'].append(file_handler)

        logger.configure(**config)
    except Exception:
        logger.exception('Error initiating logger.')
        raise
