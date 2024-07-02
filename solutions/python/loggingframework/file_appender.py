from log_appender import LogAppender

class FileAppender(LogAppender):
    def __init__(self, file_path):
        self.file_path = file_path
    
    def append(self, log_message):
        with open(self.file_path, "a") as file:
            file.write(str(log_message) + "\n")