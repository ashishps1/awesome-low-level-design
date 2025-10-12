from abc import ABC, abstractmethod
from typing import List
from library_item import LibraryItem

class SearchStrategy(ABC):
    @abstractmethod
    def search(self, query: str, items: List[LibraryItem]) -> List[LibraryItem]:
        pass

class SearchByTitleStrategy(SearchStrategy):
    def search(self, query: str, items: List[LibraryItem]) -> List[LibraryItem]:
        return [item for item in items if query.lower() in item.get_title().lower()]

class SearchByAuthorStrategy(SearchStrategy):
    def search(self, query: str, items: List[LibraryItem]) -> List[LibraryItem]:
        return [item for item in items if query.lower() in item.get_author_or_publisher().lower()]