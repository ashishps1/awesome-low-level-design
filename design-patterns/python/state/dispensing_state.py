from .machine_state import MachineState
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from .vending_machine import VendingMachine


class DispensingState(MachineState):
    """Concrete State - Dispensing item in progress"""
    
    def insert_coin(self, machine: 'VendingMachine') -> None:
        print("Please wait, dispensing item in progress.")
    
    def select_item(self, machine: 'VendingMachine') -> None:
        print("Please wait, dispensing item in progress.")
    
    def dispense_item(self, machine: 'VendingMachine') -> None:
        print("Item dispensed. Thank you!")
        from .idle_state import IdleState
        machine.set_state(IdleState())
    
    def cancel_transaction(self, machine: 'VendingMachine') -> None:
        print("Cannot cancel, item is being dispensed.")