from datetime import datetime

class Message:
    def __init__(self, message_id: str, sender, receiver, content: str, timestamp: datetime):
        self._id = message_id
        self._sender = sender
        self._receiver = receiver
        self._content = content
        self._timestamp = timestamp

    @property
    def id(self) -> str:
        return self._id

    @property
    def sender(self):
        return self._sender

    @property
    def receiver(self):
        return self._receiver

    @property
    def content(self) -> str:
        return self._content

    @property
    def timestamp(self) -> datetime:
        return self._timestamp
