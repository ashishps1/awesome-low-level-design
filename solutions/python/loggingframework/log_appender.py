from abc import ABC, abstractmethod

class LogAppender(ABC):
    @abstractmethod
    def append(self, log_message):
        pass