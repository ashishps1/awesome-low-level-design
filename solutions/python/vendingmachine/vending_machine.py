from inventory import Inventory
from idle_state import IdleState
from ready_state import ReadyState
from dispense_state import DispenseState
from return_change_state import ReturnChangeState

class VendingMachine:
    def __init__(self):
        self.inventory = Inventory()
        self.idle_state = IdleState(self)
        self.ready_state = ReadyState(self)
        self.dispense_state = DispenseState(self)
        self.return_change_state = ReturnChangeState(self)
        self.state = self.idle_state
        self.selected_product = None
        self.total_payment = 0

    def select_product(self, product):
        self.state.select_product(product)

    def insert_coin(self, coin):
        self.state.insert_coin(coin)

    def insert_note(self, note):
        self.state.insert_note(note)

    def dispense_product(self):
        self.state.dispense_product()

    def return_change(self):
        self.state.return_change()

    def add_coin(self, coin):
        self.total_payment += coin.value

    def add_note(self, note):
        self.total_payment += note.value

    def reset_payment(self):
        self.total_payment = 0