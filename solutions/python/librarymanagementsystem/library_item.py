from abc import ABC, abstractmethod
from typing import List, Optional
from member import Member
from book_copy import BookCopy

class LibraryItem(ABC):
    def __init__(self, item_id: str, title: str):
        self.id = item_id
        self.title = title
        self.copies: List['BookCopy'] = []
        self.observers: List[Member] = []  # Observer Pattern: List of members waiting for this item

    def add_copy(self, book_copy: 'BookCopy') -> None:
        self.copies.append(book_copy)

    def add_observer(self, member: Member) -> None:
        self.observers.append(member)

    def remove_observer(self, member: Member) -> None:
        if member in self.observers:
            self.observers.remove(member)

    def notify_observers(self) -> None:
        print(f"Notifying {len(self.observers)} observers for '{self.title}'...")
        # Use a copy to avoid modification during iteration
        for observer in self.observers.copy():
            observer.update(self)

    def get_available_copy(self) -> Optional['BookCopy']:
        for book_copy in self.copies:
            if book_copy.is_available():
                return book_copy
        return None

    def get_id(self) -> str:
        return self.id

    def get_title(self) -> str:
        return self.title

    def get_copies(self) -> List['BookCopy']:
        return self.copies

    @abstractmethod
    def get_author_or_publisher(self) -> str:
        pass

    def get_available_copy_count(self) -> int:
        return sum(1 for book_copy in self.copies if book_copy.is_available())

    def has_observers(self) -> bool:
        return len(self.observers) > 0

    def is_observer(self, member: Member) -> bool:
        return member in self.observers