from strategy import NewsFeedGenerationStrategy, ChronologicalStrategy
from user import User
from typing import List
from commentable_entity import Post

class NewsFeedService:
    def __init__(self):
        self.strategy = ChronologicalStrategy()  # Default strategy

    def set_strategy(self, strategy: NewsFeedGenerationStrategy):
        self.strategy = strategy

    def get_news_feed(self, user: User) -> List[Post]:
        return self.strategy.generate_feed(user)