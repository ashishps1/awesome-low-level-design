from typing import List
from loan import Loan
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from library_item import LibraryItem
    from loan import Loan

class Member:
    def __init__(self, member_id: str, name: str):
        self.id = member_id
        self.name = name
        self.loans: List['Loan'] = []

    def update(self, item: 'LibraryItem') -> None:
        """Observer update method"""
        print(f"NOTIFICATION for {self.name}: The book '{item.get_title()}' you placed a hold on is now available!")

    def add_loan(self, loan: 'Loan') -> None:
        self.loans.append(loan)

    def remove_loan(self, loan: 'Loan') -> None:
        if loan in self.loans:
            self.loans.remove(loan)

    def get_id(self) -> str:
        return self.id

    def get_name(self) -> str:
        return self.name

    def get_loans(self) -> List['Loan']:
        return self.loans