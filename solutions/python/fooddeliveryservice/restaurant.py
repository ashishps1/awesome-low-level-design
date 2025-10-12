import uuid
from order_observer import OrderObserver
from address import Address
from menu import Menu
from menu_item import MenuItem
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from order import Order

class Restaurant(OrderObserver):
    def __init__(self, name: str, address: Address):
        self.id = str(uuid.uuid4())
        self.name = name
        self.address = address
        self.menu = Menu()

    def get_id(self) -> str:
        return self.id

    def get_name(self) -> str:
        return self.name

    def get_address(self) -> Address:
        return self.address

    def get_menu(self) -> Menu:
        return self.menu

    def add_to_menu(self, item: MenuItem):
        self.menu.add_item(item)

    def on_update(self, order: 'Order'):
        print(f"--- Notification for Restaurant {self.name} ---")
        print(f"  Order {order.get_id()} has been updated to {order.get_status().value}.")
        print("----------------------------------------\n")