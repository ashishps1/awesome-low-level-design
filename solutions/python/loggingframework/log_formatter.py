from abc import ABC, abstractmethod
from log_message import LogMessage

class LogFormatter(ABC):
    @abstractmethod
    def format(self, log_message: LogMessage) -> str:
        pass

class SimpleTextFormatter(LogFormatter):
    def format(self, log_message: LogMessage) -> str:
        timestamp_str = log_message.get_timestamp().strftime("%Y-%m-%d %H:%M:%S.%f")[:-3]
        return f"{timestamp_str} [{log_message.get_thread_name()}] {log_message.get_level().name} - {log_message.get_logger_name()}: {log_message.get_message()}\n"