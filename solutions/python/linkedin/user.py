from typing import List
from profile import Profile
from connection import Connection
from message import Message

class User:
    def __init__(self, id: str, name: str, email: str, password: str, profile: Profile, connections: List[Connection], inbox: List[Message], sent_messages: List[Message]):
        self.id = id
        self.name = name
        self.email = email
        self.password = password
        self.profile = profile
        self.connections = connections
        self.inbox = inbox
        self.sent_messages = sent_messages

    def set_profile(self, profile: Profile):
        self.profile = profile