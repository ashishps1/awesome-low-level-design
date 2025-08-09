from user import User
from address import Address
from typing import List
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from order import Order

class Customer(User):
    def __init__(self, name: str, phone: str, address: Address):
        super().__init__(name, phone)
        self.address = address
        self.order_history: List['Order'] = []

    def add_order_to_history(self, order: 'Order'):
        self.order_history.append(order)

    def get_address(self) -> Address:
        return self.address

    def on_update(self, order: 'Order'):
        print(f"--- Notification for Customer {self.get_name()} ---")
        print(f"  Order {order.get_id()} is now {order.get_status().value}.")
        print("-------------------------------------\n")