from enum import Enum

class ConnectionStatus(Enum):
    PENDING = "PENDING"
    ACCEPTED = "ACCEPTED"
    REJECTED = "REJECTED"
    WITHDRAWN = "WITHDRAWN"

class NotificationType(Enum):
    CONNECTION_REQUEST = "CONNECTION_REQUEST"
    POST_LIKE = "POST_LIKE"
    POST_COMMENT = "POST_COMMENT"