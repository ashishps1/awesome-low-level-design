from vending_machine_state import VendingMachineState

class ReturnChangeState(VendingMachineState):
    def select_product(self, product):
        print("Please collect the change first.")

    def insert_coin(self, coin):
        print("Please collect the change first.")

    def insert_note(self, note):
        print("Please collect the change first.")

    def dispense_product(self):
        print("Product already dispensed. Please collect the change.")

    def return_change(self):
        change = self.vending_machine.total_payment - self.vending_machine.selected_product.price
        if change > 0:
            print(f"Change returned: ${change}")
            self.vending_machine.reset_payment()
        else:
            print("No change to return.")
        self.vending_machine.selected_product = None
        self.vending_machine.state = self.vending_machine.idle_state