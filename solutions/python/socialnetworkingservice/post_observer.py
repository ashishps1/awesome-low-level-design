from abc import ABC, abstractmethod
from user import User
from commentable_entity import Post, Comment

class PostObserver(ABC):
    @abstractmethod
    def on_post_created(self, post: Post):
        pass

    @abstractmethod
    def on_like(self, post: Post, user: User):
        pass

    @abstractmethod
    def on_comment(self, post: Post, comment: Comment):
        pass

class UserNotifier(PostObserver):
    def on_post_created(self, post: Post):
        author = post.get_author()
        for friend in author.get_friends():
            print(f"Notification for {friend.get_name()}: {author.get_name()} created a new post: {post.get_content()}")

    def on_like(self, post: Post, user: User):
        author = post.get_author()
        print(f"Notification for {author.get_name()}: {user.get_name()} liked your post")

    def on_comment(self, post: Post, comment: Comment):
        author = post.get_author()
        print(f"Notification for {author.get_name()}: {comment.get_author().get_name()} commented on your post")