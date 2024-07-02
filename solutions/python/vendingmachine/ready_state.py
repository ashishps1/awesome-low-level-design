from vending_machine_state import VendingMachineState

class ReadyState(VendingMachineState):
    def select_product(self, product):
        print("Product already selected. Please make payment.")

    def insert_coin(self, coin):
        self.vending_machine.add_coin(coin)
        print(f"Coin inserted: {coin}")
        self.check_payment_status()

    def insert_note(self, note):
        self.vending_machine.add_note(note)
        print(f"Note inserted: {note}")
        self.check_payment_status()

    def dispense_product(self):
        print("Please make payment first.")

    def return_change(self):
        change = self.vending_machine.total_payment - self.vending_machine.selected_product.price
        if change > 0:
            print(f"Change returned: ${change}")
            self.vending_machine.reset_payment()
        else:
            print("No change to return.")
        self.vending_machine.state = self.vending_machine.idle_state

    def check_payment_status(self):
        if self.vending_machine.total_payment >= self.vending_machine.selected_product.price:
            self.vending_machine.state = self.vending_machine.dispense_state