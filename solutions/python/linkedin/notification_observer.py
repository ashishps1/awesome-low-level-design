from abc import ABC, abstractmethod
from typing import List
from notification import Notification

class NotificationObserver(ABC):
    @abstractmethod
    def update(self, notification: 'Notification') -> None:
        pass

class Subject:
    def __init__(self):
        self.observers: List[NotificationObserver] = []

    def add_observer(self, observer: NotificationObserver) -> None:
        self.observers.append(observer)

    def remove_observer(self, observer: NotificationObserver) -> None:
        if observer in self.observers:
            self.observers.remove(observer)

    def notify_observers(self, notification: 'Notification') -> None:
        for observer in self.observers:
            observer.update(notification)