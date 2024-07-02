from vending_machine_state import VendingMachineState
from product import Product
from coin import Coin
from note import Note

class IdleState(VendingMachineState):
    def __init__(self, vending_machine):
        self.vending_machine = vending_machine

    def select_product(self, product: Product):
        if self.vending_machine.inventory.is_available(product):
            self.vending_machine.selected_product = product
            self.vending_machine.set_state(self.vending_machine.ready_state)
            print(f"Product selected: {product.name}")
        else:
            print(f"Product not available: {product.name}")

    def insert_coin(self, coin: Coin):
        print("Please select a product first.")

    def insert_note(self, note: Note):
        print("Please select a product first.")

    def dispense_product(self):
        print("Please select a product and make payment.")

    def return_change(self):
        print("No change to return.")