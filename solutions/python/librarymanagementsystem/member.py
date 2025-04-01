from typing import List
from book import Book

class Member:
    def __init__(self, member_id: str, name: str, contact_info: str):
        self._member_id = member_id
        self._name = name
        self._contact_info = contact_info
        self._borrowed_books = []

    @property
    def member_id(self) -> str:
        return self._member_id

    @property
    def name(self) -> str:
        return self._name

    @property
    def contact_info(self) -> str:
        return self._contact_info

    @property
    def borrowed_books(self) -> List[Book]:
        return self._borrowed_books

    def borrow_book(self, book: Book):
        self._borrowed_books.append(book)

    def return_book(self, book: Book):
        self._borrowed_books.remove(book)
