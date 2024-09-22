import os
import logging
from logging import LogRecord
from pathlib import Path
from logging import handlers
from om_log_config import CONSOLE_CONF

log_config = CONSOLE_CONF.get("log")


def _get_log_file_path(project):
    logger_file = log_config.get("log_file")
    logger_dir = log_config.get("log_dir")

    if logger_file:
        if not logger_dir:
            return logger_file
        else:
            return os.path.join(logger_dir, logger_file)

    if logger_dir:
        if not os.path.exists(logger_dir):
            os.makedirs(logger_dir)
        return os.path.join(logger_dir, "{}.log".format(project))

    return ''


SENSITIVE_STR = [
    'Password', 'passWord', 'PASSWORD', 'password', 'Pswd',
    'PSWD', 'pwd', 'signature', 'HmacSHA256', 'newPasswd',
    'private', 'certfile', 'secret', 'token', 'Token', 'pswd',
    'passwd', 'mysql -u', 'session', 'cookie'
]


class DefaultLogFilter(logging.Filter):
    def filter(self, record: LogRecord) -> int:
        msg_upper = record.getMessage().upper()
        for item in SENSITIVE_STR:
            if item.upper() in msg_upper:
                return False
        return True


def setup(project_name, console_info=True):
    """
    init log config
    :param console_info:设置屏显是否打印info日志
    :param project_name:
    """
    set_info = logging.INFO if console_info else logging.ERROR
    console = logging.StreamHandler()
    console.setLevel(set_info)
    console_formatter = logging.Formatter('[%(levelname)s ] %(message)s')
    console.setFormatter(console_formatter)

    log_root = logging.getLogger(project_name)
    for handler in list(log_root.handlers):
        log_root.removeHandler(handler)

    log_path = _get_log_file_path(project_name)
    file_log = handlers.RotatingFileHandler(
        log_path, maxBytes=log_config.get("log_file_max_size"),
        backupCount=log_config.get("log_file_backup_count"))
    file_log.setFormatter(
        logging.Formatter(
            fmt=log_config.get("logging_context_format_string"),
            datefmt=log_config.get("log_date_format")))
    log_root.addHandler(file_log)
    log_root.addHandler(console)
    log_root.addFilter(DefaultLogFilter())

    if log_config.get("debug"):
        log_root.setLevel(logging.DEBUG)
    else:
        log_root.setLevel(logging.INFO)
    return log_root


LOGGER = setup("om_deploy")
REST_LOG = setup("rest_request", console_info=False)
DR_DEPLOY_LOG = setup("dr_deploy", console_info=False)
log_directory = log_config.get("log_dir")
os.chmod(log_directory, 0o750)
os.chmod(f'{str(Path(log_directory, "om_deploy.log"))}', 0o640)
os.chmod(f'{str(Path(log_directory, "rest_request.log"))}', 0o640)
os.chmod(f'{str(Path(log_directory, "dr_deploy.log"))}', 0o640)
