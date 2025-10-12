from typing import Dict
from menu_item import MenuItem

class Menu:
    def __init__(self):
        self.items: Dict[str, MenuItem] = {}

    def add_item(self, item: MenuItem):
        self.items[item.get_id()] = item

    def get_item(self, item_id: str) -> MenuItem:
        return self.items.get(item_id)

    def get_items(self) -> Dict[str, MenuItem]:
        return self.items