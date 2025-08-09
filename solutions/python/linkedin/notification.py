from enums import NotificationType
import uuid
from datetime import datetime

class Notification:
    def __init__(self, member_id: str, notification_type: NotificationType, content: str):
        self.id = str(uuid.uuid4())
        self.member_id = member_id
        self.type = notification_type
        self.content = content
        self.created_at = datetime.now()
        self._is_read = False

    def get_content(self) -> str:
        return self.content

    def mark_as_read(self) -> None:
        self._is_read = True

    def is_read(self) -> bool:
        return self._is_read