from datetime import date
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from book_copy import BookCopy
    from member import Member

class Loan:
    def __init__(self, book_copy: 'BookCopy', member: 'Member'):
        self.copy = book_copy
        self.member = member
        self.checkout_date = date.today()

    def get_copy(self) -> 'BookCopy':
        return self.copy

    def get_member(self) -> 'Member':
        return self.member