from order_item import OrderItem
from typing import List

class Order:
    def __init__(self, order_id: int, table_id: int):
        self._order_id = order_id
        self._table_id = table_id
        self._items: List[OrderItem] = []
    
    def add_item(self, item: OrderItem):
        self._items.append(item)
    
    def get_total_price(self) -> float:
        return sum(item.menu_item.get_price() for item in self._items)
    
    @property
    def order_id(self) -> int:
        return self._order_id
    
    @property
    def table_id(self) -> int:
        return self._table_id
    
    @property
    def order_items(self) -> List[OrderItem]:
        return self._items