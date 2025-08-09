from typing import Dict, List
from member import Member
from post import Post
from feed_sorting_strategy import FeedSortingStrategy
from newsfeed import NewsFeed
from collections import defaultdict
import threading

class NewsFeedService:
    def __init__(self):
        self.all_posts: Dict[str, List[Post]] = defaultdict(list)
        self.lock = threading.Lock()

    def add_post(self, member: Member, post: Post) -> None:
        with self.lock:
            self.all_posts[member.get_id()].append(post)

    def get_member_posts(self, member: Member) -> List[Post]:
        return self.all_posts.get(member.get_id(), [])

    def display_feed_for_member(self, member: Member, feed_sorting_strategy: FeedSortingStrategy) -> None:
        feed_posts = []
        
        for connection in member.get_connections():
            connection_posts = self.all_posts.get(connection.get_id(), [])
            feed_posts.extend(connection_posts)

        news_feed = NewsFeed(feed_posts)
        news_feed.display(feed_sorting_strategy)