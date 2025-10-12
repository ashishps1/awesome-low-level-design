from abc import ABC, abstractmethod
from typing import TYPE_CHECKING
from coin import Coin

if TYPE_CHECKING:
    from .vending_machine import VendingMachine


class VendingMachineState(ABC):
    """Abstract base class for all vending machine states."""
    
    def __init__(self, machine: 'VendingMachine'):
        self.machine = machine
    
    @abstractmethod
    def insert_coin(self, coin: Coin):
        """Handle coin insertion."""
        pass
    
    @abstractmethod
    def select_item(self, code: str):
        """Handle item selection."""
        pass
    
    @abstractmethod
    def dispense(self):
        """Handle dispense request."""
        pass
    
    @abstractmethod
    def refund(self):
        """Handle refund request."""
        pass


class IdleState(VendingMachineState):
    """State when machine is waiting for user interaction."""
    
    def insert_coin(self, coin: Coin):
        print("Please select an item before inserting money.")
    
    def select_item(self, code: str):
        if not self.machine.get_inventory().is_available(code):
            print("Item not available.")
            return
        
        self.machine.set_selected_item_code(code)
        # Import here to avoid circular dependency
        from states import ItemSelectedState
        self.machine.set_state(ItemSelectedState(self.machine))
        print(f"Item selected: {code}")
    
    def dispense(self):
        print("No item selected.")
    
    def refund(self):
        print("No money to refund.")


class ItemSelectedState(VendingMachineState):
    """State when an item has been selected but insufficient money inserted."""
    
    def insert_coin(self, coin: Coin):
        self.machine.add_balance(coin.get_value())
        print(f"Coin inserted: {coin.get_value()}¢ ({coin.name})")
        
        selected_item = self.machine.get_selected_item()
        if selected_item and self.machine.get_balance() >= selected_item.get_price():
            print("Sufficient money received.")
            # Import here to avoid circular dependency
            from states import HasMoneyState
            self.machine.set_state(HasMoneyState(self.machine))
    
    def select_item(self, code: str):
        print("Item already selected. Please insert money or request refund to select a different item.")
    
    def dispense(self):
        print("Please insert sufficient money.")
    
    def refund(self):
        self.machine.refund_balance()
        self.machine.reset()
        # Import here to avoid circular dependency
        from states import IdleState
        self.machine.set_state(IdleState(self.machine))


class HasMoneyState(VendingMachineState):
    """State when sufficient money has been inserted."""
    
    def insert_coin(self, coin: Coin):
        # Allow more coins (will be returned as change)
        self.machine.add_balance(coin.get_value())
        print(f"Additional coin inserted: {coin.get_value()}¢ ({coin.name}) - will be returned as change.")
    
    def select_item(self, code: str):
        print("Item already selected. Please dispense or request refund to select a different item.")
    
    def dispense(self):
        # Import here to avoid circular dependency
        from states import DispensingState
        self.machine.set_state(DispensingState(self.machine))
        self.machine.dispense_item()
    
    def refund(self):
        self.machine.refund_balance()
        self.machine.reset()
        # Import here to avoid circular dependency
        from states import IdleState
        self.machine.set_state(IdleState(self.machine))


class DispensingState(VendingMachineState):
    """State when item is being dispensed - blocks all user input."""
    
    def insert_coin(self, coin: Coin):
        print("Currently dispensing. Please wait.")
    
    def select_item(self, code: str):
        print("Currently dispensing. Please wait.")
    
    def dispense(self):
        # Already triggered by HasMoneyState
        print("Dispensing in progress...")
    
    def refund(self):
        print("Dispensing in progress. Refund not allowed.")