from abc import ABC, abstractmethod


class Notification(ABC):
    """Product interface"""
    
    @abstractmethod
    def send(self, message: str) -> None:
        pass