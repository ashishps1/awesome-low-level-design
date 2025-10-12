from typing import Dict
from enums import Ingredient
import threading

class Inventory:
    _instance = None
    _lock = threading.Lock()
    
    def __new__(cls):
        if cls._instance is None:
            with cls._lock:
                if cls._instance is None:
                    cls._instance = super().__new__(cls)
                    cls._instance._initialized = False
        return cls._instance
    
    def __init__(self):
        if not self._initialized:
            self._stock: Dict[Ingredient, int] = {}
            self._lock = threading.Lock()
            self._initialized = True
    
    @classmethod
    def get_instance(cls):
        return cls()
    
    def add_stock(self, ingredient: Ingredient, quantity: int):
        self._stock[ingredient] = self._stock.get(ingredient, 0) + quantity
    
    def has_ingredients(self, recipe: Dict[Ingredient, int]) -> bool:
        return all(self._stock.get(ingredient, 0) >= quantity 
                  for ingredient, quantity in recipe.items())
    
    def deduct_ingredients(self, recipe: Dict[Ingredient, int]):
        with self._lock:
            if not self.has_ingredients(recipe):
                print("Not enough ingredients to make coffee.")
                return
            
            for ingredient, quantity in recipe.items():
                self._stock[ingredient] -= quantity
    
    def print_inventory(self):
        print("--- Current Inventory ---")
        for ingredient, quantity in self._stock.items():
            print(f"{ingredient.value}: {quantity}")
        print("-------------------------")