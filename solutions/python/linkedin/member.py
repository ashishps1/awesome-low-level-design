from typing import List, Set
from profile import Profile
from notification import Notification
from notification_observer import NotificationObserver
from experience import Experience
from education import Education
import uuid

class Member(NotificationObserver):
    def __init__(self, member_id: str, name: str, email: str, profile: Profile):
        self.id = member_id
        self.name = name
        self.email = email
        self.profile = profile
        self.connections: Set['Member'] = set()
        self.notifications: List['Notification'] = []

    def get_id(self) -> str:
        return self.id

    def get_name(self) -> str:
        return self.name

    def get_email(self) -> str:
        return self.email

    def get_connections(self) -> Set['Member']:
        return self.connections

    def get_profile(self) -> Profile:
        return self.profile

    def add_connection(self, member: 'Member') -> None:
        self.connections.add(member)

    def display_profile(self) -> None:
        print(f"\n--- Profile for {self.name} ({self.email}) ---")
        self.profile.display()
        print(f"  Connections: {len(self.connections)}")

    def view_notifications(self) -> None:
        print(f"\n--- Notifications for {self.name} ---")
        unread_notifications = [n for n in self.notifications if not n.is_read()]
        
        if not unread_notifications:
            print("  No new notifications.")
            return

        for notification in unread_notifications:
            print(f"  - {notification.get_content()}")
            notification.mark_as_read()

    def update(self, notification: 'Notification') -> None:
        self.notifications.append(notification)
        print(f"Notification pushed to {self.name}: {notification.get_content()}")

    class Builder:
        def __init__(self, name: str, email: str):
            self.id = str(uuid.uuid4())
            self.name = name
            self.email = email
            self.profile = Profile()

        def with_summary(self, summary: str) -> 'Member.Builder':
            self.profile.set_summary(summary)
            return self

        def add_experience(self, experience: Experience) -> 'Member.Builder':
            self.profile.add_experience(experience)
            return self

        def add_education(self, education: Education) -> 'Member.Builder':
            self.profile.add_education(education)
            return self

        def build(self) -> 'Member':
            return Member(self.id, self.name, self.email, self.profile)