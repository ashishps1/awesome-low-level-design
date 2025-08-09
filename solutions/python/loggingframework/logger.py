from log_level import LogLevel
from log_message import LogMessage
from log_appender import LogAppender
from typing import List, Optional
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from log_manager import LogManager

class Logger:
    def __init__(self, name: str, parent: Optional['Logger']):
        self.name = name
        self.level: Optional[LogLevel] = None
        self.parent = parent
        self.appenders: List[LogAppender] = []
        self.additivity = True

    def add_appender(self, appender: LogAppender):
        self.appenders.append(appender)

    def get_appenders(self) -> List[LogAppender]:
        return self.appenders

    def set_level(self, min_level: LogLevel):
        self.level = min_level

    def set_additivity(self, additivity: bool):
        self.additivity = additivity

    def get_effective_level(self) -> LogLevel:
        logger = self
        while logger is not None:
            current_level = logger.level
            if current_level is not None:
                return current_level
            logger = logger.parent
        return LogLevel.DEBUG  # Default root level

    def log(self, message_level: LogLevel, message: str):
        if message_level.is_greater_or_equal(self.get_effective_level()):
            log_message = LogMessage(message_level, self.name, message)
            self._call_appenders(log_message)

    def _call_appenders(self, log_message: LogMessage):
        if self.appenders:
            from log_manager import LogManager
            LogManager.get_instance().get_processor().process(log_message, self.appenders)
        
        if self.additivity and self.parent is not None:
            self.parent._call_appenders(log_message)

    def debug(self, message: str):
        self.log(LogLevel.DEBUG, message)

    def info(self, message: str):
        self.log(LogLevel.INFO, message)

    def warn(self, message: str):
        self.log(LogLevel.WARN, message)

    def error(self, message: str):
        self.log(LogLevel.ERROR, message)

    def fatal(self, message: str):
        self.log(LogLevel.FATAL, message)