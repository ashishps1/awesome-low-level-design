from typing import List, Set
import uuid
from commentable_entity import Post

class User:
    def __init__(self, name: str, email: str):
        self.id = str(uuid.uuid4())
        self.name = name
        self.email = email
        self.friends: Set['User'] = set()
        self.posts: List[Post] = []

    def add_friend(self, friend: 'User'):
        self.friends.add(friend)

    def add_post(self, post: Post):
        self.posts.append(post)

    def get_id(self) -> str:
        return self.id

    def get_name(self) -> str:
        return self.name

    def get_friends(self) -> Set['User']:
        return self.friends

    def get_posts(self) -> List[Post]:
        return self.posts