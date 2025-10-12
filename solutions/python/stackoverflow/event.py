from enums import EventType
from user import User
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from post import Post

class Event:
    def __init__(self, event_type: EventType, actor: User, target_post: 'Post'):
        self.type = event_type
        self.actor = actor
        self.target_post = target_post

    def get_type(self) -> EventType:
        return self.type

    def get_actor(self) -> User:
        return self.actor

    def get_target_post(self) -> 'Post':
        return self.target_post