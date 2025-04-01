from vending_machine_state import VendingMachineState
from product import Product
from coin import Coin
from note import Note

class ReadyState(VendingMachineState):
    def __init__(self, vending_machine):
        self.vending_machine = vending_machine

    def select_product(self, product: Product):
        print("Product already selected. Please make payment.")

    def insert_coin(self, coin: Coin):
        self.vending_machine.add_coin(coin)
        print(f"Coin inserted: {coin.name}")
        self.check_payment_status()

    def insert_note(self, note: Note):
        self.vending_machine.add_note(note)
        print(f"Note inserted: {note.name}")
        self.check_payment_status()

    def dispense_product(self):
        print("Please make payment first.")

    def return_change(self):
        change = self.vending_machine.total_payment - self.vending_machine.selected_product.price
        if change > 0:
            print(f"Change returned: ${change:.2f}")
            self.vending_machine.reset_payment()
        else:
            print("No change to return.")
        self.vending_machine.set_state(self.vending_machine.idle_state)

    def check_payment_status(self):
        if self.vending_machine.total_payment >= self.vending_machine.selected_product.price:
            self.vending_machine.set_state(self.vending_machine.dispense_state)