import time

class LogMessage:
    def __init__(self, level, message):
        self.level = level
        self.message = message
        self.timestamp = int(time.time() * 1000)
    
    def get_level(self):
        return self.level
    
    def get_message(self):
        return self.message
    
    def get_timestamp(self):
        return self.timestamp
    
    def __str__(self):
        return f"[{self.level}] {self.timestamp} - {self.message}"