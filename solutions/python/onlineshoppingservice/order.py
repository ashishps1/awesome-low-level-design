import uuid
from order_observer import OrderObserver
from order_line_item import OrderLineItem
from enums import OrderStatus
from typing import List
from datetime import datetime
from customer import Customer
from address import Address
from order_states import OrderState, PlacedState
from order_observer import Subject

class Order(Subject):
    def __init__(self, customer: Customer, items: List[OrderLineItem], shipping_address: Address, total_amount: float):
        super().__init__()
        self.id = str(uuid.uuid4())[:8]
        self.customer = customer
        self.items = items
        self.shipping_address = shipping_address
        self.total_amount = total_amount
        self.order_date = datetime.now()
        self.status = OrderStatus.PLACED
        self.current_state = PlacedState()
        self.add_observer(customer)

    def ship_order(self) -> None:
        self.current_state.ship(self)

    def deliver_order(self) -> None:
        self.current_state.deliver(self)

    def cancel_order(self) -> None:
        self.current_state.cancel(self)

    def get_id(self) -> str:
        return self.id

    def get_status(self) -> OrderStatus:
        return self.status

    def set_state(self, state: OrderState) -> None:
        self.current_state = state

    def set_status(self, status: OrderStatus) -> None:
        self.status = status
        self.notify_observers(self)

    def get_items(self) -> List[OrderLineItem]:
        return self.items