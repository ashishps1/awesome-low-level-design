from abc import ABC, abstractmethod
from typing import Dict
from enums import Ingredient

class Coffee(ABC):
    def __init__(self):
        self.coffee_type = "Unknown Coffee"
    
    def get_coffee_type(self) -> str:
        return self.coffee_type
    
    # The Template Method
    def prepare(self):
        print(f"\nPreparing your {self.get_coffee_type()}...")
        self._grind_beans()
        self._brew()
        self.add_condiments()  # The "hook" for base coffee types
        self._pour_into_cup()
        print(f"{self.get_coffee_type()} is ready!")
    
    # Common steps
    def _grind_beans(self):
        print("- Grinding fresh coffee beans.")
    
    def _brew(self):
        print("- Brewing coffee with hot water.")
    
    def _pour_into_cup(self):
        print("- Pouring into a cup.")
    
    # Abstract step to be implemented by subclasses
    @abstractmethod
    def add_condiments(self):
        pass
    
    @abstractmethod
    def get_price(self) -> int:
        pass
    
    @abstractmethod
    def get_recipe(self) -> Dict[Ingredient, int]:
        pass

class Espresso(Coffee):
    def __init__(self):
        super().__init__()
        self.coffee_type = "Espresso"
    
    def add_condiments(self):
        pass  # No extra condiments for espresso
    
    def get_price(self) -> int:
        return 150
    
    def get_recipe(self) -> Dict[Ingredient, int]:
        return {Ingredient.COFFEE_BEANS: 7, Ingredient.WATER: 30}

class Cappuccino(Coffee):
    def __init__(self):
        super().__init__()
        self.coffee_type = "Cappuccino"
    
    def add_condiments(self):
        print("- Adding steamed milk and foam.")
    
    def get_price(self) -> int:
        return 250
    
    def get_recipe(self) -> Dict[Ingredient, int]:
        return {Ingredient.COFFEE_BEANS: 7, Ingredient.WATER: 30, Ingredient.MILK: 100}

class Latte(Coffee):
    def __init__(self):
        super().__init__()
        self.coffee_type = "Latte"
    
    def add_condiments(self):
        print("- Adding steamed milk.")
    
    def get_price(self) -> int:
        return 220
    
    def get_recipe(self) -> Dict[Ingredient, int]:
        return {Ingredient.COFFEE_BEANS: 7, Ingredient.WATER: 30, Ingredient.MILK: 150}