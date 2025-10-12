from library_item import LibraryItem

class Magazine(LibraryItem):
    def __init__(self, item_id: str, title: str, publisher: str):
        super().__init__(item_id, title)
        self.publisher = publisher

    def get_author_or_publisher(self) -> str:
        return self.publisher