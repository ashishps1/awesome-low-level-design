from abc import ABC, abstractmethod
from inventory import Inventory
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from coffee_vending_machine import CoffeeVendingMachine
    from coffee import Coffee

class VendingMachineState(ABC):
    @abstractmethod
    def select_coffee(self, machine: 'CoffeeVendingMachine', coffee: 'Coffee'):
        pass
    
    @abstractmethod
    def insert_money(self, machine: 'CoffeeVendingMachine', amount: int):
        pass
    
    @abstractmethod
    def dispense_coffee(self, machine: 'CoffeeVendingMachine'):
        pass
    
    @abstractmethod
    def cancel(self, machine: 'CoffeeVendingMachine'):
        pass

class ReadyState(VendingMachineState):
    def select_coffee(self, machine: 'CoffeeVendingMachine', coffee: 'Coffee'):
        machine.set_selected_coffee(coffee)
        machine.set_state(SelectingState())
        print(f"{coffee.get_coffee_type()} selected. Price: {coffee.get_price()}")
    
    def insert_money(self, machine: 'CoffeeVendingMachine', amount: int):
        print("Please select a coffee first.")
    
    def dispense_coffee(self, machine: 'CoffeeVendingMachine'):
        print("Please select and pay first.")
    
    def cancel(self, machine: 'CoffeeVendingMachine'):
        print("Nothing to cancel.")

class SelectingState(VendingMachineState):
    def select_coffee(self, machine: 'CoffeeVendingMachine', coffee: 'Coffee'):
        print("Already selected. Please pay or cancel.")
    
    def insert_money(self, machine: 'CoffeeVendingMachine', amount: int):
        machine.set_money_inserted(machine.get_money_inserted() + amount)
        print(f"Inserted {amount}. Total: {machine.get_money_inserted()}")
        if machine.get_money_inserted() >= machine.get_selected_coffee().get_price():
            machine.set_state(PaidState())
    
    def dispense_coffee(self, machine: 'CoffeeVendingMachine'):
        print("Please insert enough money first.")
    
    def cancel(self, machine: 'CoffeeVendingMachine'):
        print(f"Transaction cancelled. Refunding {machine.get_money_inserted()}")
        machine.reset()
        machine.set_state(ReadyState())

class PaidState(VendingMachineState):
    def select_coffee(self, machine: 'CoffeeVendingMachine', coffee: 'Coffee'):
        print("Already paid. Please dispense or cancel.")
    
    def insert_money(self, machine: 'CoffeeVendingMachine', amount: int):
        machine.set_money_inserted(machine.get_money_inserted() + amount)
        print(f"Additional {amount} inserted. Total: {machine.get_money_inserted()}")
    
    def dispense_coffee(self, machine: 'CoffeeVendingMachine'):
        inventory = Inventory.get_instance()
        coffee = machine.get_selected_coffee()
        
        if not inventory.has_ingredients(coffee.get_recipe()):
            print("Sorry, we are out of ingredients. Refunding your money.")
            print(f"Refunding {machine.get_money_inserted()}")
            machine.reset()
            machine.set_state(OutOfIngredientState())
            return
        
        # Deduct ingredients and prepare coffee
        inventory.deduct_ingredients(coffee.get_recipe())
        coffee.prepare()
        
        # Calculate change
        change = machine.get_money_inserted() - coffee.get_price()
        if change > 0:
            print(f"Here's your change: {change}")
        
        machine.reset()
        machine.set_state(ReadyState())
    
    def cancel(self, machine: 'CoffeeVendingMachine'):
        print(f"Transaction cancelled. Refunding {machine.get_money_inserted()}")
        machine.reset()
        machine.set_state(ReadyState())


class OutOfIngredientState(VendingMachineState):
    def select_coffee(self, machine: 'CoffeeVendingMachine', coffee: 'Coffee'):
        print("Sorry, we are sold out.")
    
    def insert_money(self, machine: 'CoffeeVendingMachine', amount: int):
        print("Sorry, we are sold out. Money refunded.")
    
    def dispense_coffee(self, machine: 'CoffeeVendingMachine'):
        print("Sorry, we are sold out.")
    
    def cancel(self, machine: 'CoffeeVendingMachine'):
        print(f"Refunding {machine.get_money_inserted()}")
        machine.reset()
        machine.set_state(ReadyState())