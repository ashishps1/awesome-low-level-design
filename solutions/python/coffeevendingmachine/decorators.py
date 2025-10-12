from coffee import Coffee
from typing import Dict
from enums import Ingredient

class CoffeeDecorator(Coffee):
    def __init__(self, coffee: Coffee):
        super().__init__()
        self.decorated_coffee = coffee
    
    def get_price(self) -> int:
        return self.decorated_coffee.get_price()
    
    def get_recipe(self) -> Dict[Ingredient, int]:
        return self.decorated_coffee.get_recipe()
    
    def add_condiments(self):
        self.decorated_coffee.add_condiments()
    
    def prepare(self):
        self.decorated_coffee.prepare()

class CaramelSyrupDecorator(CoffeeDecorator):
    COST = 30
    RECIPE_ADDITION = {Ingredient.CARAMEL_SYRUP: 10}
    
    def __init__(self, coffee: Coffee):
        super().__init__(coffee)
    
    def get_coffee_type(self) -> str:
        return self.decorated_coffee.get_coffee_type() + ", Caramel Syrup"
    
    def get_price(self) -> int:
        return self.decorated_coffee.get_price() + self.COST
    
    def get_recipe(self) -> Dict[Ingredient, int]:
        new_recipe = self.decorated_coffee.get_recipe().copy()
        for ingredient, qty in self.RECIPE_ADDITION.items():
            new_recipe[ingredient] = new_recipe.get(ingredient, 0) + qty
        return new_recipe
    
    def prepare(self):
        # First, prepare the underlying coffee
        super().prepare()
        # Then, add the specific step for this decorator
        print("- Drizzling Caramel Syrup on top.")

class ExtraSugarDecorator(CoffeeDecorator):
    COST = 10
    RECIPE_ADDITION = {Ingredient.SUGAR: 1}
    
    def __init__(self, coffee: Coffee):
        super().__init__(coffee)
    
    def get_coffee_type(self) -> str:
        return self.decorated_coffee.get_coffee_type() + ", Extra Sugar"
    
    def get_price(self) -> int:
        return self.decorated_coffee.get_price() + self.COST
    
    def get_recipe(self) -> Dict[Ingredient, int]:
        new_recipe = self.decorated_coffee.get_recipe().copy()
        for ingredient, qty in self.RECIPE_ADDITION.items():
            new_recipe[ingredient] = new_recipe.get(ingredient, 0) + qty
        return new_recipe
    
    def prepare(self):
        super().prepare()
        print("- Stirring in Extra Sugar.")