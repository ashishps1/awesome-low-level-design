from coffee_machine import CoffeeMachine
from payment import Payment

class CoffeeVendingMachineDemo:
    @staticmethod
    def run():
        coffee_machine = CoffeeMachine.get_instance()

        # Display coffee menu
        coffee_machine.display_menu()

        # Simulate user requests
        espresso = coffee_machine.select_coffee("Espresso")
        coffee_machine.dispense_coffee(espresso, Payment(3.0))

        cappuccino = coffee_machine.select_coffee("Cappuccino")
        coffee_machine.dispense_coffee(cappuccino, Payment(3.5))

        latte = coffee_machine.select_coffee("Latte")
        coffee_machine.dispense_coffee(latte, Payment(4.0))


if __name__ == "__main__":
    CoffeeVendingMachineDemo.run()