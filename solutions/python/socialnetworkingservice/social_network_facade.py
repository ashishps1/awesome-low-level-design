from user_service import UserService
from post_service import PostService
from newsfeed_service import NewsFeedService
from post_observer import UserNotifier
from user import User
from typing import List
from commentable_entity import Post

class SocialNetworkFacade:
    def __init__(self):
        self.user_service = UserService()
        self.post_service = PostService()
        self.news_feed_service = NewsFeedService()
        # Wire up the observer
        self.post_service.add_observer(UserNotifier())

    def create_user(self, name: str, email: str) -> User:
        return self.user_service.create_user(name, email)

    def add_friend(self, user_id1: str, user_id2: str):
        self.user_service.add_friend(user_id1, user_id2)

    def create_post(self, author_id: str, content: str) -> Post:
        author = self.user_service.get_user_by_id(author_id)
        return self.post_service.create_post(author, content)

    def add_comment(self, user_id: str, post_id: str, content: str):
        user = self.user_service.get_user_by_id(user_id)
        self.post_service.add_comment(user, post_id, content)

    def like_post(self, user_id: str, post_id: str):
        user = self.user_service.get_user_by_id(user_id)
        self.post_service.like_post(user, post_id)

    def get_news_feed(self, user_id: str) -> List[Post]:
        user = self.user_service.get_user_by_id(user_id)
        return self.news_feed_service.get_news_feed(user)