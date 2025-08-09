from abc import ABC, abstractmethod
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from order_item import OrderItem

class OrderItemState(ABC):
    @abstractmethod
    def next(self, item: 'OrderItem'):
        pass
    
    @abstractmethod
    def prev(self, item: 'OrderItem'):
        pass
    
    @abstractmethod
    def get_status(self) -> str:
        pass

class OrderedState(OrderItemState):
    def next(self, item: 'OrderItem'):
        item.set_state(PreparingState())
    
    def prev(self, item: 'OrderItem'):
        print("This is the initial state.")
    
    def get_status(self) -> str:
        return "ORDERED"

class PreparingState(OrderItemState):
    def next(self, item: 'OrderItem'):
        item.set_state(ReadyForPickupState())
    
    def prev(self, item: 'OrderItem'):
        item.set_state(OrderedState())
    
    def get_status(self) -> str:
        return "PREPARING"

class ReadyForPickupState(OrderItemState):
    def next(self, item: 'OrderItem'):
        # This is the key state. When it transitions, it notifies observers.
        item.notify_observers()
    
    def prev(self, item: 'OrderItem'):
        item.set_state(PreparingState())
    
    def get_status(self) -> str:
        return "READY_FOR_PICKUP"

class ServedState(OrderItemState):
    def next(self, item: 'OrderItem'):
        print("This is the final state.")
    
    def prev(self, item: 'OrderItem'):
        print("Cannot revert a served item.")
    
    def get_status(self) -> str:
        return "SERVED"