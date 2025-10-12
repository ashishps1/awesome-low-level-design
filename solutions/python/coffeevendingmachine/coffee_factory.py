from enums import CoffeeType
from coffee import Coffee, Espresso, Latte, Cappuccino

class CoffeeFactory:
    @staticmethod
    def create_coffee(coffee_type: CoffeeType) -> Coffee:
        if coffee_type == CoffeeType.ESPRESSO:
            return Espresso()
        elif coffee_type == CoffeeType.LATTE:
            return Latte()
        elif coffee_type == CoffeeType.CAPPUCCINO:
            return Cappuccino()
        else:
            raise ValueError(f"Unsupported coffee type: {coffee_type}")