from datetime import datetime
from typing import List, Dict, Optional
from threading import Lock
import uuid
from user import User
from job_posting import JobPosting
from connection import Connection
from notification import Notification, NotificationType
from message import Message

class LinkedInService:
    _instance = None
    _lock = Lock()

    def __new__(cls):
        with cls._lock:
            if cls._instance is None:
                cls._instance = super().__new__(cls)
                cls._instance.users: Dict[str, User] = {}
                cls._instance.job_postings: Dict[str, JobPosting] = {}
                cls._instance.notifications: Dict[str, List[Notification]] = {}
        return cls._instance

    def register_user(self, user: User):
        self.users[user.id] = user

    def login_user(self, email: str, password: str) -> Optional[User]:
        for user in self.users.values():
            if user.email == email and user.password == password:
                return user
        return None

    def update_user_profile(self, user: User):
        self.users[user.id] = user

    def send_connection_request(self, sender: User, receiver: User):
        connection = Connection(sender, datetime.now())
        receiver.connections.append(connection)
        notification = Notification(self._generate_notification_id(), receiver,
                                    NotificationType.CONNECTION_REQUEST,
                                    f"New connection request from {sender.name}",
                                    datetime.now())
        self._add_notification(receiver.id, notification)

    def accept_connection_request(self, user: User, connection_user: User):
        for connection in user.connections:
            if connection.user == connection_user:
                user.connections.append(Connection(connection_user, datetime.now()))
                break

    def search_users(self, keyword: str) -> List[User]:
        return [user for user in self.users.values() if keyword.lower() in user.name.lower()]

    def post_job_listing(self, job_posting: JobPosting):
        self.job_postings[job_posting.id] = job_posting
        for user in self.users.values():
            notification = Notification(self._generate_notification_id(), user,
                                        NotificationType.JOB_POSTING,
                                        f"New job posting: {job_posting.title}",
                                        datetime.now())
            self._add_notification(user.id, notification)

    def search_job_postings(self, keyword: str) -> List[JobPosting]:
        return [job for job in self.job_postings.values()
                if keyword.lower() in job.title.lower() or keyword.lower() in job.description.lower()]

    def send_message(self, sender: User, receiver: User, content: str):
        message = Message(self._generate_message_id(), sender, receiver, content, datetime.now())
        receiver.inbox.append(message)
        sender.sent_messages.append(message)
        notification = Notification(self._generate_notification_id(), receiver,
                                    NotificationType.MESSAGE,
                                    f"New message from {sender.name}",
                                    datetime.now())
        self._add_notification(receiver.id, notification)

    def _add_notification(self, user_id: str, notification: Notification):
        if user_id not in self.notifications:
            self.notifications[user_id] = []
        self.notifications[user_id].append(notification)

    def get_notifications(self, user_id: str) -> List[Notification]:
        return self.notifications.get(user_id, [])

    def _generate_notification_id(self) -> str:
        return str(uuid.uuid4())

    def _generate_message_id(self) -> str:
        return str(uuid.uuid4())