import threading
from typing import Dict, List, Optional
from member import Member
from connection_service import ConnectionService
from newsfeed_service import NewsFeedService
from search_service import SearchService
from notification_service import NotificationService
from feed_sorting_strategy import ChronologicalSortStrategy
from post import Post

class LinkedInSystem:
    _instance: Optional['LinkedInSystem'] = None
    _lock = threading.Lock()

    def __new__(cls):
        if cls._instance is None:
            with cls._lock:
                if cls._instance is None:
                    cls._instance = super().__new__(cls)
        return cls._instance

    def __init__(self):
        if hasattr(self, 'initialized'):
            return

        self.members: Dict[str, Member] = {}
        self.connection_service = ConnectionService(NotificationService())
        self.news_feed_service = NewsFeedService()
        self.search_service = SearchService(self.members.values())
        self.initialized = True

    @classmethod
    def get_instance(cls) -> 'LinkedInSystem':
        return cls()

    def register_member(self, member: Member) -> None:
        self.members[member.get_id()] = member
        print(f"New member registered: {member.get_name()}")

    def get_member(self, name: str) -> Optional[Member]:
        for member in self.members.values():
            if member.get_name() == name:
                return member
        return None

    def send_connection_request(self, from_member: Member, to_member: Member) -> str:
        return self.connection_service.send_request(from_member, to_member)

    def accept_connection_request(self, request_id: str) -> None:
        self.connection_service.accept_request(request_id)

    def create_post(self, member_id: str, content: str) -> None:
        author = self.members[member_id]
        post = Post(author, content)
        self.news_feed_service.add_post(author, post)
        print(f"{author.get_name()} created a new post.")

    def get_latest_post_by_member(self, member_id: str) -> Optional[Post]:
        member_posts = self.news_feed_service.get_member_posts(self.members[member_id])
        if not member_posts:
            return None
        return member_posts[-1]

    def view_news_feed(self, member_id: str) -> None:
        member = self.members[member_id]
        print(f"\n--- News Feed for {member.get_name()} ---")
        self.news_feed_service.display_feed_for_member(member, ChronologicalSortStrategy())

    def search_member_by_name(self, name: str) -> List[Member]:
        return self.search_service.search_by_name(name)