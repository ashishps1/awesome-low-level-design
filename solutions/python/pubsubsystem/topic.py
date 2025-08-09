from subscriber import Subscriber
from message import Message
from typing import Set
from concurrent.futures import ThreadPoolExecutor

class Topic:
    def __init__(self, name: str, delivery_executor: ThreadPoolExecutor):
        self.name = name
        self.delivery_executor = delivery_executor
        self.subscribers: Set[Subscriber] = set()

    def get_name(self) -> str:
        return self.name

    def add_subscriber(self, subscriber: Subscriber):
        self.subscribers.add(subscriber)

    def remove_subscriber(self, subscriber: Subscriber):
        self.subscribers.discard(subscriber)

    def broadcast(self, message: Message):
        for subscriber in self.subscribers:
            self.delivery_executor.submit(self._deliver_message, subscriber, message)

    def _deliver_message(self, subscriber: Subscriber, message: Message):
        try:
            subscriber.on_message(message)
        except Exception as e:
            print(f"Error delivering message to subscriber {subscriber.get_id()}: {str(e)}")