from typing import List, Dict
from collections import defaultdict
from book import Book
from member import Member

class LibraryManager:
    _instance = None

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
            cls._instance.catalog = {}
            cls._instance.members = {}
            cls._instance.MAX_BOOKS_PER_MEMBER = 5
            cls._instance.LOAN_DURATION_DAYS = 14
        return cls._instance

    @staticmethod
    def get_instance():
        if LibraryManager._instance is None:
            LibraryManager()
        return LibraryManager._instance

    def add_book(self, book: Book):
        self.catalog[book.isbn] = book

    def remove_book(self, isbn: str):
        self.catalog.pop(isbn, None)

    def get_book(self, isbn: str) -> Book:
        return self.catalog.get(isbn)

    def register_member(self, member: Member):
        self.members[member.member_id] = member

    def unregister_member(self, member_id: str):
        self.members.pop(member_id, None)

    def get_member(self, member_id: str) -> Member:
        return self.members.get(member_id)

    def borrow_book(self, member_id: str, isbn: str):
        member = self.get_member(member_id)
        book = self.get_book(isbn)

        if member and book and book.available:
            if len(member.borrowed_books) < self.MAX_BOOKS_PER_MEMBER:
                member.borrow_book(book)
                book.available = False
                print(f"Book borrowed: {book.title} by {member.name}")
            else:
                print(f"Member {member.name} has reached the maximum number of borrowed books.")
        else:
            print("Book or member not found, or book is not available.")

    def return_book(self, member_id: str, isbn: str):
        member = self.get_member(member_id)
        book = self.get_book(isbn)

        if member and book:
            member.return_book(book)
            book.available = True
            print(f"Book returned: {book.title} by {member.name}")
        else:
            print("Book or member not found.")

    def search_books(self, keyword: str) -> List[Book]:
        matching_books = [book for book in self.catalog.values() if keyword in book.title or keyword in book.author]
        return matching_books
