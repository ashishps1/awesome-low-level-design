from member import Member
from notification import Notification

class NotificationService:
    def send_notification(self, member: Member, notification: Notification) -> None:
        member.update(notification)