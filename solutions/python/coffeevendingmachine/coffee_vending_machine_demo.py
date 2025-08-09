from coffee_vending_machine import CoffeeVendingMachine
from inventory import Inventory
from enums import CoffeeType, ToppingType, Ingredient

class CoffeeVendingMachineDemo:
    @staticmethod
    def main():
        machine = CoffeeVendingMachine.get_instance()
        inventory = Inventory.get_instance()
        
        # Initial setup: Refill inventory
        print("=== Initializing Vending Machine ===")
        inventory.add_stock(Ingredient.COFFEE_BEANS, 50)
        inventory.add_stock(Ingredient.WATER, 500)
        inventory.add_stock(Ingredient.MILK, 200)
        inventory.add_stock(Ingredient.SUGAR, 100)
        inventory.add_stock(Ingredient.CARAMEL_SYRUP, 50)
        inventory.print_inventory()
        
        # Scenario 1: Successful Purchase of a Latte
        print("\n--- SCENARIO 1: Buy a Latte (Success) ---")
        machine.select_coffee(CoffeeType.LATTE, [])
        machine.insert_money(200)
        machine.insert_money(50)  # Total 250, price is 220
        machine.dispense_coffee()
        inventory.print_inventory()
        
        # Scenario 2: Purchase with Insufficient Funds & Cancellation
        print("\n--- SCENARIO 2: Buy Espresso (Insufficient Funds & Cancel) ---")
        machine.select_coffee(CoffeeType.ESPRESSO, [])
        machine.insert_money(100)  # Price is 150
        machine.dispense_coffee()  # Should fail
        machine.cancel()  # Should refund 100
        inventory.print_inventory()  # Should be unchanged
        
        # Scenario 3: Attempt to Buy with Insufficient Ingredients
        print("\n--- SCENARIO 3: Buy Cappuccino (Out of Milk) ---")
        inventory.print_inventory()
        machine.select_coffee(CoffeeType.CAPPUCCINO, [ToppingType.CARAMEL_SYRUP, ToppingType.EXTRA_SUGAR])
        machine.insert_money(300)
        machine.dispense_coffee()  # Should fail and refund
        inventory.print_inventory()
        
        # Refill and final test
        print("\n--- REFILLING AND FINAL TEST ---")
        inventory.add_stock(Ingredient.MILK, 200)
        inventory.print_inventory()
        machine.select_coffee(CoffeeType.LATTE, [ToppingType.CARAMEL_SYRUP])
        machine.insert_money(250)
        machine.dispense_coffee()
        inventory.print_inventory()

if __name__ == "__main__":
    CoffeeVendingMachineDemo.main()