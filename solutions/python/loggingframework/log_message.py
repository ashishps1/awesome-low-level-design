import threading
from datetime import datetime
from log_level import LogLevel

class LogMessage:
    def __init__(self, level: LogLevel, logger_name: str, message: str):
        self.timestamp = datetime.now()
        self.level = level
        self.logger_name = logger_name
        self.message = message
        self.thread_name = threading.current_thread().name

    def get_timestamp(self) -> datetime:
        return self.timestamp

    def get_level(self) -> LogLevel:
        return self.level

    def get_logger_name(self) -> str:
        return self.logger_name

    def get_thread_name(self) -> str:
        return self.thread_name

    def get_message(self) -> str:
        return self.message