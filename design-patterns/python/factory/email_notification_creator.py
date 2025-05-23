from .notification_creator import NotificationCreator
from .email_notification import EmailNotification
from .notification import Notification


class EmailNotificationCreator(NotificationCreator):
    """Concrete Creator"""
    
    def create_notification(self) -> Notification:
        return EmailNotification()