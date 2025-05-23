from .notification_creator import NotificationCreator
from .sms_notification import SMSNotification
from .notification import Notification


class SMSNotificationCreator(NotificationCreator):
    """Concrete Creator"""
    
    def create_notification(self) -> Notification:
        return SMSNotification()