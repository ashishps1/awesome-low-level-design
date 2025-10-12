from abc import ABC, abstractmethod
from message import Message

class Subscriber(ABC):
    @abstractmethod
    def get_id(self) -> str:
        pass

    @abstractmethod
    def on_message(self, message: Message):
        pass

class AlertSubscriber(Subscriber):
    def __init__(self, subscriber_id: str):
        self.id = subscriber_id

    def get_id(self) -> str:
        return self.id

    def on_message(self, message: Message):
        print(f"!!! [ALERT - {self.id}] : '{message.get_payload()}' !!!")

class NewsSubscriber(Subscriber):
    def __init__(self, subscriber_id: str):
        self.id = subscriber_id

    def get_id(self) -> str:
        return self.id

    def on_message(self, message: Message):
        print(f"[Subscriber {self.id}] received message '{message.get_payload()}'")