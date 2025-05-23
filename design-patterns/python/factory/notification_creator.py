from abc import ABC, abstractmethod
from .notification import Notification


class NotificationCreator(ABC):
    """Creator - Factory Method Pattern"""
    
    @abstractmethod
    def create_notification(self) -> Notification:
        """Factory method - to be implemented by concrete creators"""
        pass
    
    def send(self, message: str) -> None:
        """Common logic using the factory method"""
        notification = self.create_notification()
        notification.send(message)