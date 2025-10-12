from datetime import datetime
from user import User
from typing import List
from commentable_entity import Post, Comment
from social_network_facade import SocialNetworkFacade

def print_feed(feed: List[Post]):
    if not feed:
        print("  No posts in the feed.")
        return
    
    for post in feed:
        print(f"  Post by {post.get_author().get_name()} at {post.get_timestamp()}")
        print(f"    \"{post.get_content()}\"")
        print(f"    Likes: {len(post.get_likes())}, Comments: {len(post.get_comments())}")

class SocialNetworkingServiceDemo:
    def run():
        social_network = SocialNetworkFacade()

        print("----------- 1. Creating Users -----------")
        alice = social_network.create_user("Alice", "alice@example.com")
        bob = social_network.create_user("Bob", "bob@example.com")
        charlie = social_network.create_user("Charlie", "charlie@example.com")
        print(f"Created users: {alice.get_name()}, {bob.get_name()}, {charlie.get_name()}")

        print("\n----------- 2. Building Friendships -----------")
        social_network.add_friend(alice.get_id(), bob.get_id())
        social_network.add_friend(bob.get_id(), charlie.get_id())
        print(f"{alice.get_name()} and {bob.get_name()} are now friends.")
        print(f"{bob.get_name()} and {charlie.get_name()} are now friends.")

        print("\n----------- 3. Users Create Posts -----------")
        alice_post = social_network.create_post(alice.get_id(), "Hello from Alice!")
        bob_post = social_network.create_post(bob.get_id(), "It's a beautiful day!")
        charlie_post = social_network.create_post(charlie.get_id(), "Thinking about design patterns.")

        print("\n----------- 4. Users Interact with Posts -----------")
        social_network.add_comment(bob.get_id(), alice_post.get_id(), "Hey Alice, nice to see you here!")
        social_network.like_post(charlie.get_id(), alice_post.get_id())

        print("\n----------- 5. Viewing News Feeds (Strategy Pattern) -----------")

        print("\n--- Alice's News Feed (should see Bob's post) ---")
        alices_feed = social_network.get_news_feed(alice.get_id())
        print_feed(alices_feed)

        print("\n--- Bob's News Feed (should see Alice's, and Charlie's post) ---")
        bobs_feed = social_network.get_news_feed(bob.get_id())
        print_feed(bobs_feed)

        print("\n--- Charlie's News Feed (should see Bob's post) ---")
        charlies_feed = social_network.get_news_feed(charlie.get_id())
        print_feed(charlies_feed)

if __name__ == "__main__":
    SocialNetworkingServiceDemo.run()