from .notification import Notification


class PushNotification(Notification):
    """Concrete Product"""
    
    def send(self, message: str) -> None:
        print(f"Sending push notification: {message}")