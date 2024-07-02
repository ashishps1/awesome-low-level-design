from datetime import datetime
from enum import Enum

class NotificationType(Enum):
    CONNECTION_REQUEST = "CONNECTION_REQUEST"
    MESSAGE = "MESSAGE"
    JOB_POSTING = "JOB_POSTING"

class Notification:
    def __init__(self, notification_id: str, user, type: NotificationType, content: str, timestamp: datetime):
        self._id = notification_id
        self._user = user
        self._type = type
        self._content = content
        self._timestamp = timestamp

    @property
    def id(self) -> str:
        return self._id

    @property
    def user(self):
        return self._user

    @property
    def type(self) -> NotificationType:
        return self._type

    @property
    def content(self) -> str:
        return self._content

    @property
    def timestamp(self) -> datetime:
        return self._timestamp
