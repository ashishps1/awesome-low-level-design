from datetime import datetime
from typing import List, Dict
from collections import defaultdict
import itertools
import uuid
from user import User
from job_posting import JobPosting
from connection import Connection
from notification import Notification, NotificationType
from message import Message

class LinkedInService:
    _instance = None

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
            cls._instance.users = {}
            cls._instance.job_postings = {}
            cls._instance.notifications = defaultdict(list)
        return cls._instance

    @staticmethod
    def get_instance():
        if LinkedInService._instance is None:
            LinkedInService()
        return LinkedInService._instance

    def register_user(self, user: User):
        self.users[user.id] = user

    def login_user(self, email: str, password: str) -> User:
        for user in self.users.values():
            if user.email == email and user.password == password:
                return user
        return None

    def update_user_profile(self, user: User):
        self.users[user.id] = user

    def send_connection_request(self, sender: User, receiver: User):
        connection = Connection(sender, datetime.now())
        receiver.connections.append(connection)
        notification = Notification(uuid.uuid4().hex, receiver, NotificationType.CONNECTION_REQUEST, f"New connection request from {sender.name}", datetime.now())
        self.add_notification(receiver.id, notification)

    def accept_connection_request(self, user: User, connection_user: User):
        for connection in user.connections:
            if connection.user == connection_user:
                user.connections.append(Connection(connection_user, datetime.now()))
                break

    def search_users(self, keyword: str) -> List[User]:
        return [user for user in self.users.values() if keyword in user.name or keyword in user.profile.headline]

    def post_job_listing(self, job_posting: JobPosting):
        self.job_postings[job_posting.id] = job_posting
        for user in self.users.values():
            notification = Notification(uuid.uuid4().hex, user, NotificationType.JOB_POSTING, f"New job posting: {job_posting.title}", datetime.now())
            self.add_notification(user.id, notification)

    def search_job_postings(self, keyword: str) -> List[JobPosting]:
        return [job for job in self.job_postings.values() if keyword in job.title or keyword in job.description]

    def send_message(self, sender: User, receiver: User, content: str):
        message = Message(uuid.uuid4().hex, sender, receiver, content, datetime.now())
        receiver.inbox.append(message)
        sender.sent_messages.append(message)
        notification = Notification(uuid.uuid4().hex, receiver, NotificationType.MESSAGE, f"New message from {sender.name}", datetime.now())
        self.add_notification(receiver.id, notification)

    def add_notification(self, user_id: str, notification: Notification):
        self.notifications[user_id].append(notification)

    def get_notifications(self, user_id: str) -> List[Notification]:
        return self.notifications[user_id]
