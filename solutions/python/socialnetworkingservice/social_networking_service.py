import uuid
from datetime import datetime
from concurrent.futures import ThreadPoolExecutor
from notification import Notification, NotificationType

class SocialNetworkingService:
    _instance = None
    _lock = ThreadPoolExecutor(max_workers=1)

    def __new__(cls):
        if not cls._instance:
            with cls._lock:
                if not cls._instance:
                    cls._instance = super().__new__(cls)
                    cls._instance._initialize()
        return cls._instance

    def _initialize(self):
        self.users = {}
        self.posts = {}
        self.notifications = {}

    def register_user(self, user):
        self.users[user.get_id()] = user

    def login_user(self, email, password):
        for user in self.users.values():
            if user.get_email() == email and user.get_password() == password:
                return user
        return None

    def update_user_profile(self, user):
        self.users[user.get_id()] = user

    def send_friend_request(self, sender_id, receiver_id):
        receiver = self.users.get(receiver_id)
        if receiver:
            notification = Notification(str(uuid.uuid4()), receiver_id, NotificationType.FRIEND_REQUEST,
                                        f"Friend request from {sender_id}", datetime.now())
            self._add_notification(receiver_id, notification)

    def accept_friend_request(self, user_id, friend_id):
        user = self.users.get(user_id)
        friend = self.users.get(friend_id)
        if user and friend:
            user.get_friends().append(friend_id)
            friend.get_friends().append(user_id)
            notification = Notification(str(uuid.uuid4()), friend_id, NotificationType.FRIEND_REQUEST_ACCEPTED,
                                        f"Friend request accepted by {user_id}", datetime.now())
            self._add_notification(friend_id, notification)

    def create_post(self, post):
        self.posts[post.get_id()] = post
        user = self.users.get(post.get_user_id())
        if user:
            user.get_posts().append(post)

    def get_newsfeed(self, user_id):
        newsfeed = []
        user = self.users.get(user_id)
        if user:
            friend_ids = user.get_friends()
            for friend_id in friend_ids:
                friend = self.users.get(friend_id)
                if friend:
                    newsfeed.extend(friend.get_posts())
            newsfeed.extend(user.get_posts())
            newsfeed.sort(key=lambda post: post.get_timestamp(), reverse=True)
        return newsfeed

    def like_post(self, user_id, post_id):
        post = self.posts.get(post_id)
        if post and user_id not in post.get_likes():
            post.get_likes().append(user_id)
            notification = Notification(str(uuid.uuid4()), post.get_user_id(), NotificationType.LIKE,
                                        f"Your post was liked by {user_id}", datetime.now())
            self._add_notification(post.get_user_id(), notification)

    def comment_on_post(self, comment):
        post = self.posts.get(comment.get_post_id())
        if post:
            post.get_comments().append(comment)
            notification = Notification(str(uuid.uuid4()), post.get_user_id(), NotificationType.COMMENT,
                                        f"Your post received a comment from {comment.get_user_id()}", datetime.now())
            self._add_notification(post.get_user_id(), notification)

    def _add_notification(self, user_id, notification):
        if user_id not in self.notifications:
            self.notifications[user_id] = []
        self.notifications[user_id].append(notification)

    def get_notifications(self, user_id):
        return self.notifications.get(user_id, [])