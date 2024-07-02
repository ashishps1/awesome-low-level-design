from vending_machine_state import VendingMachineState

class DispenseState(VendingMachineState):
    def select_product(self, product):
        print("Product already selected. Please collect the dispensed product.")

    def insert_coin(self, coin):
        print("Payment already made. Please collect the dispensed product.")

    def insert_note(self, note):
        print("Payment already made. Please collect the dispensed product.")

    def dispense_product(self):
        product = self.vending_machine.selected_product
        self.vending_machine.inventory.update_quantity(product, self.vending_machine.inventory.get_quantity(product) - 1)
        print(f"Product dispensed: {product.name}")
        self.vending_machine.selected_product = None
        self.vending_machine.state = self.vending_machine.return_change_state

    def return_change(self):
        print("Please collect the dispensed product first.")