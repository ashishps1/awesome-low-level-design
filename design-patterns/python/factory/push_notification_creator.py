from .notification_creator import NotificationCreator
from .push_notification import PushNotification
from .notification import Notification


class PushNotificationCreator(NotificationCreator):
    """Concrete Creator"""
    
    def create_notification(self) -> Notification:
        return PushNotification()