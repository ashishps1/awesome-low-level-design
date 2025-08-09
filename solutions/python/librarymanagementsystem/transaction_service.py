from typing import Dict, Optional, TYPE_CHECKING
from loan import Loan

if TYPE_CHECKING:
    from book_copy import BookCopy
    from member import Member

class TransactionService:
    _instance: Optional['TransactionService'] = None

    def __init__(self):
        if TransactionService._instance is not None:
            raise Exception("This class is a singleton!")
        self.active_loans: Dict[str, Loan] = {}  # Key: BookCopy ID

    @staticmethod
    def get_instance() -> 'TransactionService':
        if TransactionService._instance is None:
            TransactionService._instance = TransactionService()
        return TransactionService._instance

    def create_loan(self, book_copy: 'BookCopy', member: 'Member') -> None:
        if book_copy.get_id() in self.active_loans:
            raise ValueError("This copy is already on loan.")
        
        loan = Loan(book_copy, member)
        self.active_loans[book_copy.get_id()] = loan
        member.add_loan(loan)

    def end_loan(self, book_copy: 'BookCopy') -> None:
        loan = self.active_loans.pop(book_copy.get_id(), None)
        if loan is not None:
            loan.get_member().remove_loan(loan)