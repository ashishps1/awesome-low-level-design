import threading
from user import User
from address import Address
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from order import Order

class DeliveryAgent(User):
    def __init__(self, name: str, phone: str, current_location: Address):
        super().__init__(name, phone)
        self.is_available = True
        self.current_location = current_location
        self._lock = threading.Lock()

    def set_available(self, available: bool):
        with self._lock:
            self.is_available = available

    def is_available_agent(self) -> bool:
        with self._lock:
            return self.is_available

    def set_current_location(self, current_location: Address):
        self.current_location = current_location

    def get_current_location(self) -> Address:
        return self.current_location

    def on_update(self, order: 'Order'):
        print(f"--- Notification for Delivery Agent {self.get_name()} ---")
        print(f"  Order {order.get_id()} update: Status is {order.get_status().value}.")
        print("-------------------------------------------\n")