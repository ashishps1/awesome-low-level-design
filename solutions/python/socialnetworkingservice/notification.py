from enum import Enum

class NotificationType(Enum):
    FRIEND_REQUEST = 1
    FRIEND_REQUEST_ACCEPTED = 2
    LIKE = 3
    COMMENT = 4
    MENTION = 5

class Notification:
    def __init__(self, id, user_id, notification_type, content, timestamp):
        self.id = id
        self.user_id = user_id
        self.type = notification_type
        self.content = content
        self.timestamp = timestamp

    def get_id(self):
        return self.id

    def get_user_id(self):
        return self.user_id

    def get_type(self):
        return self.type

    def get_content(self):
        return self.content

    def get_timestamp(self):
        return self.timestamp