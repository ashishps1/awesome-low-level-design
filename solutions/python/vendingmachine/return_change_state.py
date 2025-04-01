from vending_machine_state import VendingMachineState
from product import Product
from coin import Coin
from note import Note

class ReturnChangeState(VendingMachineState):
    def __init__(self, vending_machine):
        self.vending_machine = vending_machine

    def select_product(self, product: Product):
        print("Please collect the change first.")

    def insert_coin(self, coin: Coin):
        print("Please collect the change first.")

    def insert_note(self, note: Note):
        print("Please collect the change first.")

    def dispense_product(self):
        print("Product already dispensed. Please collect the change.")

    def return_change(self):
        change = self.vending_machine.total_payment - self.vending_machine.selected_product.price
        if change > 0:
            print(f"Change returned: ${change:.2f}")
            self.vending_machine.reset_payment()
        else:
            print("No change to return.")
        self.vending_machine.reset_selected_product()
        self.vending_machine.set_state(self.vending_machine.idle_state)