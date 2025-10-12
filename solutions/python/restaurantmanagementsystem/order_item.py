from menu_item import MenuItem
from typing import List
from order_observer import OrderObserver
from order_item_states import OrderItemState, OrderedState
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from order import Order

class OrderItem:
    def __init__(self, menu_item: MenuItem, order: 'Order'):
        self._menu_item = menu_item
        self._order = order
        self._state = OrderedState()
        self._observers: List[OrderObserver] = []
    
    def change_state(self, new_state: OrderItemState):
        self._state = new_state
        print(f"Item '{self._menu_item.get_name()}' state changed to: {new_state.get_status()}")
    
    def next_state(self):
        self._state.next(self)
    
    def set_state(self, state: OrderItemState):
        self._state = state
    
    def add_observer(self, observer: OrderObserver):
        self._observers.append(observer)
    
    def notify_observers(self):
        for observer in self._observers[:]:  # Create a copy to avoid modification during iteration
            observer.update(self)
    
    @property
    def menu_item(self) -> MenuItem:
        return self._menu_item
    
    @property
    def order(self) -> 'Order':
        return self._order