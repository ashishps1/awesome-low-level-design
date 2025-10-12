from typing import TYPE_CHECKING
from item_states import AvailableState

if TYPE_CHECKING:
    from member import Member
    from library_item import LibraryItem
    from item_states import ItemState

class BookCopy:
    def __init__(self, copy_id: str, item: 'LibraryItem'):
        self.id = copy_id
        self.item = item
        self.current_state: 'ItemState' = AvailableState()
        item.add_copy(self)

    def checkout(self, member: 'Member') -> None:
        self.current_state.checkout(self, member)

    def return_item(self) -> None:
        self.current_state.return_item(self)

    def place_hold(self, member: 'Member') -> None:
        self.current_state.place_hold(self, member)

    def set_state(self, state: 'ItemState') -> None:
        self.current_state = state

    def get_id(self) -> str:
        return self.id

    def get_item(self) -> 'LibraryItem':
        return self.item

    def is_available(self) -> bool:
        return isinstance(self.current_state, AvailableState)