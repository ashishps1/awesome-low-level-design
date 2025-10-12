from abc import ABC, abstractmethod
from typing import List
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from order import Order

class OrderObserver(ABC):
    @abstractmethod
    def update(self, order: 'Order') -> None:
        pass

class Subject:
    def __init__(self):
        self.observers: List[OrderObserver] = []

    def add_observer(self, observer: OrderObserver) -> None:
        self.observers.append(observer)

    def remove_observer(self, observer: OrderObserver) -> None:
        if observer in self.observers:
            self.observers.remove(observer)

    def notify_observers(self, order: 'Order') -> None:
        for observer in self.observers:
            observer.update(order)