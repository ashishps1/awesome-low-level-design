from .notification import Notification


class SMSNotification(Notification):
    """Concrete Product"""
    
    def send(self, message: str) -> None:
        print(f"Sending SMS: {message}")