from abc import ABC, abstractmethod
from transaction_service import TransactionService
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from book_copy import BookCopy
    from member import Member

class ItemState(ABC):
    @abstractmethod
    def checkout(self, book_copy: 'BookCopy', member: 'Member') -> None:
        pass

    @abstractmethod
    def return_item(self, book_copy: 'BookCopy') -> None:
        pass

    @abstractmethod
    def place_hold(self, book_copy: 'BookCopy', member: 'Member') -> None:
        pass


class AvailableState(ItemState):
    def checkout(self, book_copy: 'BookCopy', member: 'Member') -> None:
        TransactionService.get_instance().create_loan(book_copy, member)
        book_copy.set_state(CheckedOutState())
        print(f"{book_copy.get_id()} checked out by {member.get_name()}")

    def return_item(self, book_copy: 'BookCopy') -> None:
        print("Cannot return an item that is already available.")

    def place_hold(self, book_copy: 'BookCopy', member: 'Member') -> None:
        print("Cannot place hold on an available item. Please check it out.")


class CheckedOutState(ItemState):
    def checkout(self, book_copy: 'BookCopy', member: 'Member') -> None:
        print(f"{book_copy.get_id()} is already checked out.")

    def return_item(self, book_copy: 'BookCopy') -> None:
        TransactionService.get_instance().end_loan(book_copy)
        print(f"{book_copy.get_id()} returned.")
        
        # If there are holds, move to OnHold state. Otherwise, become Available.
        if book_copy.get_item().has_observers():
            book_copy.set_state(OnHoldState())
            book_copy.get_item().notify_observers()  # Notify members that item is back but on hold
        else:
            book_copy.set_state(AvailableState())

    def place_hold(self, book_copy: 'BookCopy', member: 'Member') -> None:
        book_copy.get_item().add_observer(member)
        print(f"{member.get_name()} placed a hold on '{book_copy.get_item().get_title()}'")


class OnHoldState(ItemState):
    def checkout(self, book_copy: 'BookCopy', member: 'Member') -> None:
        # Only a member who placed the hold can check it out.
        if book_copy.get_item().is_observer(member):
            TransactionService.get_instance().create_loan(book_copy, member)
            book_copy.get_item().remove_observer(member)  # Remove from waiting list
            book_copy.set_state(CheckedOutState())
            print(f"Hold fulfilled. {book_copy.get_id()} checked out by {member.get_name()}")
        else:
            print("This item is on hold for another member.")

    def return_item(self, book_copy: 'BookCopy') -> None:
        print("Invalid action. Item is on hold, not checked out.")

    def place_hold(self, book_copy: 'BookCopy', member: 'Member') -> None:
        print("Item is already on hold.")