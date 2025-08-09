from item_type import ItemType
from book import Book
from magazine import Magazine
from library_item import LibraryItem

class ItemFactory:
    @staticmethod
    def create_item(item_type: ItemType, item_id: str, title: str, author: str) -> LibraryItem:
        if item_type == ItemType.BOOK:
            return Book(item_id, title, author)
        elif item_type == ItemType.MAGAZINE:
            return Magazine(item_id, title, author)  # Author might be publisher here
        else:
            raise ValueError("Unknown item type")