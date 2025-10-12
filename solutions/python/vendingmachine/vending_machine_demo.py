from vending_machine import VendingMachine
from coin import Coin

class VendingMachineDemo:
    @staticmethod
    def main():
        vending_machine = VendingMachine.get_instance()

        # Add products to the inventory
        vending_machine.add_item("A1", "Coke", 25, 3)
        vending_machine.add_item("A2", "Pepsi", 25, 2)
        vending_machine.add_item("B1", "Water", 10, 5)

        # Select a product
        print("\n--- Step 1: Select an item ---")
        vending_machine.select_item("A1")

        # Insert coins
        print("\n--- Step 2: Insert coins ---")
        vending_machine.insert_coin(Coin.DIME)  # 10
        vending_machine.insert_coin(Coin.DIME)  # 10
        vending_machine.insert_coin(Coin.NICKEL)  # 5

        # Dispense the product
        print("\n--- Step 3: Dispense item ---")
        vending_machine.dispense()  # Should dispense Coke

        # Select another item
        print("\n--- Step 4: Select another item ---")
        vending_machine.select_item("B1")

        # Insert more amount
        print("\n--- Step 5: Insert more than needed ---")
        vending_machine.insert_coin(Coin.QUARTER)  # 25

        # Try to dispense the product
        print("\n--- Step 6: Dispense and return change ---")
        vending_machine.dispense()


if __name__ == "__main__":
    VendingMachineDemo.main()