from .machine_state import MachineState
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from .vending_machine import VendingMachine


class IdleState(MachineState):
    """Concrete State - Machine is idle waiting for coin"""
    
    def insert_coin(self, machine: 'VendingMachine') -> None:
        print("Coin inserted. Please select an item.")
        from .item_selected_state import ItemSelectedState
        machine.set_state(ItemSelectedState())
    
    def select_item(self, machine: 'VendingMachine') -> None:
        print("Please insert a coin first.")
    
    def dispense_item(self, machine: 'VendingMachine') -> None:
        print("Please insert a coin and select an item first.")
    
    def cancel_transaction(self, machine: 'VendingMachine') -> None:
        print("No transaction to cancel.")