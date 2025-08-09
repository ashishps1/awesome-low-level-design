from typing import Dict, Optional
from item import Item

class Inventory:
    def __init__(self):
        self.item_map: Dict[str, Item] = {}
        self.stock_map: Dict[str, int] = {}

    def add_item(self, code: str, item: Item, quantity: int) -> None:
        self.item_map[code] = item
        self.stock_map[code] = quantity

    def get_item(self, code: str) -> Optional[Item]:
        return self.item_map.get(code)

    def is_available(self, code: str) -> bool:
        return self.stock_map.get(code, 0) > 0

    def reduce_stock(self, code: str) -> None:
        self.stock_map[code] = self.stock_map[code] - 1