from datetime import datetime
from social_networking_service import SocialNetworkingService
from user import User
from post import Post
from comment import Comment

class SocialNetworkingServiceDemo:
    def run():
        social_networking_service = SocialNetworkingService()

        # User registration
        user1 = User("1", "John Doe", "john@example.com", "password", "profile1.jpg", "I love coding!", [], [])
        user2 = User("2", "Jane Smith", "jane@example.com", "password", "profile2.jpg", "Exploring the world!", [], [])
        social_networking_service.register_user(user1)
        social_networking_service.register_user(user2)

        # User login
        logged_in_user = social_networking_service.login_user("john@example.com", "password")
        if logged_in_user:
            print(f"User logged in: {logged_in_user.get_name()}")
        else:
            print("Invalid email or password.")

        # Send friend request
        social_networking_service.send_friend_request(user1.get_id(), user2.get_id())

        # Accept friend request
        social_networking_service.accept_friend_request(user2.get_id(), user1.get_id())

        # Create posts
        post1 = Post("post1", user1.get_id(), "My first post!", [], [], datetime.now(), [], [])
        post2 = Post("post2", user2.get_id(), "Having a great day!", [], [], datetime.now(), [], [])
        social_networking_service.create_post(post1)
        social_networking_service.create_post(post2)

        # Like a post
        social_networking_service.like_post(user2.get_id(), post1.get_id())

        # Comment on a post
        comment = Comment("comment1", user2.get_id(), post1.get_id(), "Great post!", datetime.now())
        social_networking_service.comment_on_post(comment)

        # Get newsfeed
        newsfeed = social_networking_service.get_newsfeed(user1.get_id())
        print("Newsfeed:")
        for post in newsfeed:
            print(f"Post: {post.get_content()}")
            print(f"Likes: {len(post.get_likes())}")
            print(f"Comments: {len(post.get_comments())}")
            print()

        # Get notifications
        notifications = social_networking_service.get_notifications(user1.get_id())
        print("Notifications:")
        for notification in notifications:
            print(f"Type: {notification.get_type()}")
            print(f"Content: {notification.get_content()}")
            print()

if __name__ == "__main__":
    SocialNetworkingServiceDemo.run()