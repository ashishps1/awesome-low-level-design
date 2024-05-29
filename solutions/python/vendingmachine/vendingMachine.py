from abc import ABC, abstractmethod
from enum import Enum

class Product:
    def __init__(self, name, price):
        self.name = name
        self.price = price

class Coin(Enum):
    PENNY = 0.01
    NICKEL = 0.05
    DIME = 0.1
    QUARTER = 0.25

class Note(Enum):
    ONE = 1
    FIVE = 5
    TEN = 10
    TWENTY = 20

class Inventory:
    def __init__(self):
        self.products = {}

    def add_product(self, product, quantity):
        self.products[product] = quantity

    def remove_product(self, product):
        del self.products[product]

    def update_quantity(self, product, quantity):
        self.products[product] = quantity

    def get_quantity(self, product):
        return self.products.get(product, 0)

    def is_available(self, product):
        return product in self.products and self.products[product] > 0

class VendingMachineState(ABC):
    def __init__(self, vending_machine):
        self.vending_machine = vending_machine

    @abstractmethod
    def select_product(self, product):
        pass

    @abstractmethod
    def insert_coin(self, coin):
        pass

    @abstractmethod
    def insert_note(self, note):
        pass

    @abstractmethod
    def dispense_product(self):
        pass

    @abstractmethod
    def return_change(self):
        pass

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

def main():
    vending_machine = VendingMachine()

    # Add products to the inventory
    coke = Product("Coke", 1.5)
    pepsi = Product("Pepsi", 1.5)
    water = Product("Water", 1.0)

    vending_machine.inventory.add_product(coke, 5)
    vending_machine.inventory.add_product(pepsi, 3)
    vending_machine.inventory.add_product(water, 2)

    # Select a product
    vending_machine.select_product(coke)

    # Insert coins
    vending_machine.insert_coin(Coin.QUARTER)
    vending_machine.insert_coin(Coin.QUARTER)
    vending_machine.insert_coin(Coin.QUARTER)
    vending_machine.insert_coin(Coin.QUARTER)

    # Insert a note
    vending_machine.insert_note(Note.FIVE)

    # Dispense the product
    vending_machine.dispense_product()

    # Return change
    vending_machine.return_change()

    # Select another product
    vending_machine.select_product(pepsi)

    # Insert insufficient payment
    vending_machine.insert_coin(Coin.QUARTER)

    # Try to dispense the product
    vending_machine.dispense_product()

    # Insert more coins
    vending_machine.insert_coin(Coin.QUARTER)
    vending_machine.insert_coin(Coin.QUARTER)
    vending_machine.insert_coin(Coin.QUARTER)
    vending_machine.insert_coin(Coin.QUARTER)

    # Dispense the product
    vending_machine.dispense_product()

    # Return change
    vending_machine.return_change()

if __name__ == "__main__":
    main()