from enum import Enum

class NotificationType(Enum):
    CONNECTION_REQUEST = "CONNECTION_REQUEST"
    MESSAGE = "MESSAGE"
    JOB_POSTING = "JOB_POSTING"