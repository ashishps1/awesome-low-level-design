from logger_config import LoggerConfig
from log_level import LogLevel
from log_message import LogMessage
from console_appender import ConsoleAppender

class Logger:
    _instance = None
    
    def __init__(self):
        if Logger._instance is not None:
            raise Exception("This class is a singleton!")
        else:
            Logger._instance = self
            self.config = LoggerConfig(LogLevel.INFO, ConsoleAppender())
    
    @staticmethod
    def get_instance():
        if Logger._instance is None:
            Logger()
        return Logger._instance
    
    def set_config(self, config):
        self.config = config
    
    def log(self, level, message):
        if level.value >= self.config.get_log_level().value:
            log_message = LogMessage(level, message)
            self.config.get_log_appender().append(log_message)
    
    def debug(self, message):
        self.log(LogLevel.DEBUG, message)
    
    def info(self, message):
        self.log(LogLevel.INFO, message)
    
    def warning(self, message):
        self.log(LogLevel.WARNING, message)
    
    def error(self, message):
        self.log(LogLevel.ERROR, message)
    
    def fatal(self, message):
        self.log(LogLevel.FATAL, message)