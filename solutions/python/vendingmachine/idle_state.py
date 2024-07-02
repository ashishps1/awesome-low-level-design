from vending_machine_state import VendingMachineState

class IdleState(VendingMachineState):
    def select_product(self, product):
        if self.vending_machine.inventory.is_available(product):
            self.vending_machine.selected_product = product
            self.vending_machine.state = self.vending_machine.ready_state
            print(f"Product selected: {product.name}")
        else:
            print(f"Product not available: {product.name}")

    def insert_coin(self, coin):
        print("Please select a product first.")

    def insert_note(self, note):
        print("Please select a product first.")

    def dispense_product(self):
        print("Please select a product and make payment.")

    def return_change(self):
        print("No change to return.")