from library_item import LibraryItem

class Book(LibraryItem):
    def __init__(self, item_id: str, title: str, author: str):
        super().__init__(item_id, title)
        self.author = author

    def get_author_or_publisher(self) -> str:
        return self.author