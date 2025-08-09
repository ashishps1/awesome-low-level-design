from order_observer import OrderObserver
import uuid
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from order import Order

class User(OrderObserver):
    def __init__(self, name: str, phone: str):
        self.id = str(uuid.uuid4())
        self.name = name
        self.phone = phone

    def get_id(self) -> str:
        return self.id

    def get_name(self) -> str:
        return self.name