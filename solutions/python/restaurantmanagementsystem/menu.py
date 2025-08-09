from typing import Dict
from menu_item import MenuItem

class Menu:
    def __init__(self):
        self._items: Dict[str, MenuItem] = {}
    
    def add_item(self, item: MenuItem):
        self._items[item.get_id()] = item
    
    def get_item(self, item_id: str) -> MenuItem:
        item = self._items.get(item_id)
        if item is None:
            raise ValueError(f"Menu item with ID {item_id} not found.")
        return item
    
    def get_all_items(self) -> Dict[str, MenuItem]:
        return self._items.copy()