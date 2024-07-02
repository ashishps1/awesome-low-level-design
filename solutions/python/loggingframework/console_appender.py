from log_appender import LogAppender

class ConsoleAppender(LogAppender):
    def append(self, log_message):
        print(log_message)