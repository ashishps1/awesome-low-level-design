from abc import ABC, abstractmethod
from enums import OrderStatus
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from order import Order

class OrderState(ABC):
    @abstractmethod
    def ship(self, order: 'Order') -> None:
        pass

    @abstractmethod
    def deliver(self, order: 'Order') -> None:
        pass

    @abstractmethod
    def cancel(self, order: 'Order') -> None:
        pass

class PlacedState(OrderState):
    def ship(self, order: 'Order') -> None:
        print(f"Shipping order {order.get_id()}")
        order.set_status(OrderStatus.SHIPPED)
        order.set_state(ShippedState())

    def deliver(self, order: 'Order') -> None:
        print("Cannot deliver an order that has not been shipped.")

    def cancel(self, order: 'Order') -> None:
        print(f"Cancelling order {order.get_id()}")
        order.set_status(OrderStatus.CANCELLED)
        order.set_state(CancelledState())

class ShippedState(OrderState):
    def ship(self, order: 'Order') -> None:
        print("Order is already shipped.")

    def deliver(self, order: 'Order') -> None:
        print(f"Delivering order {order.get_id()}")
        order.set_status(OrderStatus.DELIVERED)
        order.set_state(DeliveredState())

    def cancel(self, order: 'Order') -> None:
        print("Cannot cancel a shipped order.")

class DeliveredState(OrderState):
    def ship(self, order: 'Order') -> None:
        print("Order already delivered.")

    def deliver(self, order: 'Order') -> None:
        print("Order already delivered.")

    def cancel(self, order: 'Order') -> None:
        print("Cannot cancel a delivered order.")

class CancelledState(OrderState):
    def ship(self, order: 'Order') -> None:
        print("Cannot ship a cancelled order.")

    def deliver(self, order: 'Order') -> None:
        print("Cannot deliver a cancelled order.")

    def cancel(self, order: 'Order') -> None:
        print("Order is already cancelled.")