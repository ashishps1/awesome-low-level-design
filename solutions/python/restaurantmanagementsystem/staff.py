from abc import ABC
from typing import TYPE_CHECKING
from order import Order
from order_item import OrderItem
from order_item_states import PreparingState, ServedState
from order_observer import OrderObserver

# if TYPE_CHECKING:

class Staff(ABC):
    def __init__(self, staff_id: str, name: str):
        self._id = staff_id
        self._name = name
    
    @property
    def id(self) -> str:
        return self._id
    
    @property
    def name(self) -> str:
        return self._name

class Chef(Staff):
    def __init__(self, staff_id: str, name: str):
        super().__init__(staff_id, name)
    
    def prepare_order(self, order: 'Order'):
        print(f"Chef {self._name} received order {order.order_id} and is starting preparation.")
        for item in order.order_items:
            # Chef's action triggers the first state change for each item
            item.change_state(PreparingState())

class Waiter(Staff, OrderObserver):
    def __init__(self, staff_id: str, name: str):
        super().__init__(staff_id, name)
    
    def serve_order(self, order: 'Order'):
        print(f"Waiter {self._name} is serving order {order.order_id}")
        for item in order.order_items:
            item.change_state(ServedState())
    
    def update(self, item: 'OrderItem'):
        print(f">>> WAITER {self._name} NOTIFIED: Item '{item.menu_item.get_name()}' "
              f"for table {item.order.table_id} is READY FOR PICKUP.")