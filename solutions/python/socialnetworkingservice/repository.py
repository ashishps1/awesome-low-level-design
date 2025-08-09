from user import User
from typing import Optional
from threading import Lock
from commentable_entity import Post

class UserRepository:
    _instance = None
    _lock = Lock()

    def __new__(cls):
        if cls._instance is None:
            with cls._lock:
                if cls._instance is None:
                    cls._instance = super().__new__(cls)
                    cls._instance.users = {}
        return cls._instance

    @classmethod
    def get_instance(cls):
        return cls()

    def save(self, user: User):
        self.users[user.get_id()] = user

    def find_by_id(self, user_id: str) -> Optional[User]:
        return self.users.get(user_id)

class PostRepository:
    _instance = None
    _lock = Lock()

    def __new__(cls):
        if cls._instance is None:
            with cls._lock:
                if cls._instance is None:
                    cls._instance = super().__new__(cls)
                    cls._instance.posts = {}
        return cls._instance

    @classmethod
    def get_instance(cls):
        return cls()

    def save(self, post: Post):
        self.posts[post.get_id()] = post

    def find_by_id(self, post_id: str) -> Optional[Post]:
        return self.posts.get(post_id)