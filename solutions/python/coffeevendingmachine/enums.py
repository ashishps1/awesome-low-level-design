from enum import Enum

class CoffeeType(Enum):
    ESPRESSO = "ESPRESSO"
    LATTE = "LATTE"
    CAPPUCCINO = "CAPPUCCINO"

class Ingredient(Enum):
    COFFEE_BEANS = "COFFEE_BEANS"
    MILK = "MILK"
    SUGAR = "SUGAR"
    WATER = "WATER"
    CARAMEL_SYRUP = "CARAMEL_SYRUP"

class ToppingType(Enum):
    EXTRA_SUGAR = "EXTRA_SUGAR"
    CARAMEL_SYRUP = "CARAMEL_SYRUP"