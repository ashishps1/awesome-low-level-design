from typing import List
from enums import CoffeeType, ToppingType
from coffee import Coffee
from coffee_factory import CoffeeFactory
from decorators import ExtraSugarDecorator, CaramelSyrupDecorator
from states import VendingMachineState, ReadyState
import threading

class CoffeeVendingMachine:
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
            self._state = ReadyState()
            self._selected_coffee: Coffee = None
            self._money_inserted = 0
            self._initialized = True
    
    @classmethod
    def get_instance(cls):
        return cls()
    
    def select_coffee(self, coffee_type: CoffeeType, toppings: List[ToppingType]):
        # 1. Create the base coffee using the factory
        coffee = CoffeeFactory.create_coffee(coffee_type)
        
        # 2. Wrap it with decorators
        for topping in toppings:
            if topping == ToppingType.EXTRA_SUGAR:
                coffee = ExtraSugarDecorator(coffee)
            elif topping == ToppingType.CARAMEL_SYRUP:
                coffee = CaramelSyrupDecorator(coffee)
        
        # Let the state handle the rest
        self._state.select_coffee(self, coffee)
    
    def insert_money(self, amount: int):
        self._state.insert_money(self, amount)
    
    def dispense_coffee(self):
        self._state.dispense_coffee(self)
    
    def cancel(self):
        self._state.cancel(self)
    
    # Getters and Setters used by State objects
    def set_state(self, state: VendingMachineState):
        self._state = state
    
    def get_state(self) -> VendingMachineState:
        return self._state
    
    def set_selected_coffee(self, coffee: Coffee):
        self._selected_coffee = coffee
    
    def get_selected_coffee(self) -> Coffee:
        return self._selected_coffee
    
    def set_money_inserted(self, amount: int):
        self._money_inserted = amount
    
    def get_money_inserted(self) -> int:
        return self._money_inserted
    
    def reset(self):
        self._selected_coffee = None
        self._money_inserted = 0
