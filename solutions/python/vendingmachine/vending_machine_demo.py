from vending_machine import VendingMachine
from product import Product
from coin import Coin
from note import Note

class VendingMachineDemo:
    @staticmethod
    def run():
        vending_machine = VendingMachine.get_instance()

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
    VendingMachineDemo.run()