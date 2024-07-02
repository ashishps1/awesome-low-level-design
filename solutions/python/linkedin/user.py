from typing import List

class User:
    def __init__(self, user_id: str, name: str, email: str, password: str, profile, connections: List, inbox: List, sent_messages: List):
        self._id = user_id
        self._name = name
        self._email = email
        self._password = password
        self._profile = profile
        self._connections = connections
        self._inbox = inbox
        self._sent_messages = sent_messages

    @property
    def id(self) -> str:
        return self._id

    @property
    def name(self) -> str:
        return self._name

    @property
    def email(self) -> str:
        return self._email

    @property
    def password(self) -> str:
        return self._password

    @property
    def profile(self):
        return self._profile

    @profile.setter
    def profile(self, profile):
        self._profile = profile

    @property
    def connections(self) -> List:
        return self._connections

    @property
    def inbox(self) -> List:
        return self._inbox

    @property
    def sent_messages(self) -> List:
        return self._sent_messages
