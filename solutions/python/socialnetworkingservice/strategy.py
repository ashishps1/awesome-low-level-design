from abc import ABC, abstractmethod
from user import User
from typing import List
from commentable_entity import Post

class NewsFeedGenerationStrategy(ABC):
    @abstractmethod
    def generate_feed(self, user: User) -> List[Post]:
        pass

class ChronologicalStrategy(NewsFeedGenerationStrategy):
    def generate_feed(self, user: User) -> List[Post]:
        friends = user.get_friends()
        feed = []

        for friend in friends:
            feed.extend(friend.get_posts())

        # Sort posts by timestamp in reverse (most recent first)
        feed.sort(key=lambda p: p.get_timestamp(), reverse=True)

        return feed