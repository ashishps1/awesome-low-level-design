from typing import List
from member import Member
from notification import Notification
from notification_observer import Subject
from enums import NotificationType
import uuid
from datetime import datetime

class Like:
    def __init__(self, member: Member):
        self.member = member
        self.created_at = datetime.now()

    def get_member(self) -> Member:
        return self.member

class Comment:
    def __init__(self, author: Member, text: str):
        self.author = author
        self.text = text
        self.created_at = datetime.now()

    def get_author(self) -> Member:
        return self.author

    def get_text(self) -> str:
        return self.text

class Post(Subject):
    def __init__(self, author: Member, content: str):
        super().__init__()
        self.id = str(uuid.uuid4())
        self.author = author
        self.content = content
        self.created_at = datetime.now()
        self.likes: List[Like] = []
        self.comments: List[Comment] = []
        self.add_observer(author)

    def add_like(self, member: Member) -> None:
        self.likes.append(Like(member))
        notification_content = f"{member.get_name()} liked your post."
        notification = Notification(self.author.get_id(), NotificationType.POST_LIKE, notification_content)
        self.notify_observers(notification)

    def add_comment(self, member: Member, text: str) -> None:
        self.comments.append(Comment(member, text))
        notification_content = f"{member.get_name()} commented on your post: \"{text}\""
        notification = Notification(self.author.get_id(), NotificationType.POST_COMMENT, notification_content)
        self.notify_observers(notification)

    def get_id(self) -> str:
        return self.id

    def get_author(self) -> Member:
        return self.author

    def get_content(self) -> str:
        return self.content

    def get_created_at(self) -> datetime:
        return self.created_at

    def get_likes(self) -> List[Like]:
        return self.likes

    def get_comments(self) -> List[Comment]:
        return self.comments