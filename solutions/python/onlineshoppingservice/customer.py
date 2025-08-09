from order_observer import OrderObserver
from address import Address
from account import Account
import uuid
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from order import Order

class Customer(OrderObserver):
    def __init__(self, name: str, email: str, password: str, shipping_address: Address):
        self.id = str(uuid.uuid4())
        self.name = name
        self.email = email
        self.account = Account(email, password)
        self.shipping_address = shipping_address

    def update(self, order: 'Order') -> None:
        print(f"[Notification for {self.name}]: Your order #{order.get_id()} status has been updated to: {order.get_status().value}.")

    def get_id(self) -> str:
        return self.id

    def get_name(self) -> str:
        return self.name

    def get_account(self) -> 'Account':
        return self.account

    def get_shipping_address(self) -> Address:
        return self.shipping_address

    def set_shipping_address(self, address: Address) -> None:
        self.shipping_address = address