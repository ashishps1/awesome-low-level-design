from abc import ABC, abstractmethod
from enums import OrderStatus
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from order import Order

class OrderState(ABC):
    @abstractmethod
    def handle(self, order: 'Order') -> None:
        pass

    @abstractmethod
    def cancel(self, order: 'Order') -> None:
        pass

class OpenState(OrderState):
    def handle(self, order: 'Order') -> None:
        print("Order is open and waiting for execution.")

    def cancel(self, order: 'Order') -> None:
        order.set_status(OrderStatus.CANCELLED)
        order.set_state(CancelledState())
        print(f"Order {order.get_order_id()} has been cancelled.")

class FilledState(OrderState):
    def handle(self, order: 'Order') -> None:
        print("Order is already filled.")

    def cancel(self, order: 'Order') -> None:
        print("Cannot cancel a filled order.")

class CancelledState(OrderState):
    def handle(self, order: 'Order') -> None:
        print("Order is cancelled.")

    def cancel(self, order: 'Order') -> None:
        print("Order is already cancelled.")