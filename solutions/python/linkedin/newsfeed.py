from typing import List
from post import Post
from feed_sorting_strategy import FeedSortingStrategy

class NewsFeed:
    def __init__(self, posts: List[Post]):
        self.posts = posts

    def display(self, strategy: FeedSortingStrategy) -> None:
        sorted_posts = strategy.sort(self.posts)
        if not sorted_posts:
            print("  Your news feed is empty.")
            return

        for post in sorted_posts:
            print("----------------------------------------")
            print(f"Post by: {post.get_author().get_name()} (at {post.get_created_at().date()})")
            print(f"Content: {post.get_content()}")
            print(f"Likes: {len(post.get_likes())}, Comments: {len(post.get_comments())}")
            print("----------------------------------------")