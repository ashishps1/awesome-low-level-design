from abc import ABC, abstractmethod
from typing import List
from post import Post

class FeedSortingStrategy(ABC):
    @abstractmethod
    def sort(self, posts: List[Post]) -> List[Post]:
        pass

class ChronologicalSortStrategy(FeedSortingStrategy):
    def sort(self, posts: List[Post]) -> List[Post]:
        return sorted(posts, key=lambda post: post.get_created_at(), reverse=True)