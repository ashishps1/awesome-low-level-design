from .notification import Notification


class EmailNotification(Notification):
    """Concrete Product"""
    
    def send(self, message: str) -> None:
        print(f"Sending email: {message}")