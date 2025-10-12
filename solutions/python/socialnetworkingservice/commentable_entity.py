from datetime import datetime
from typing import List, Set
import uuid
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from user import User

class CommentableEntity:
    def __init__(self, author: 'User', content: str):
        self.id = str(uuid.uuid4())
        self.author = author
        self.content = content
        self.timestamp = datetime.now()
        self.likes: Set['User'] = set()
        self.comments: List['Comment'] = []

    def add_like(self, user: 'User'):
        self.likes.add(user)

    def add_comment(self, comment: 'Comment'):
        self.comments.append(comment)

    def get_id(self) -> str:
        return self.id

    def get_author(self) -> 'User':
        return self.author

    def get_content(self) -> str:
        return self.content

    def get_timestamp(self) -> datetime:
        return self.timestamp

    def get_comments(self) -> List['Comment']:
        return self.comments

    def get_likes(self) -> Set['User']:
        return self.likes

class Post(CommentableEntity):
    def __init__(self, author: 'User', content: str):
        super().__init__(author, content)

class Comment(CommentableEntity):
    def __init__(self, author: 'User', content: str):
        super().__init__(author, content)

    def get_replies(self) -> List['Comment']:
        return self.get_comments()