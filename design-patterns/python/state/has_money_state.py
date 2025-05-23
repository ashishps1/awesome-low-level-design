from .machine_state import MachineState
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from .vending_machine import VendingMachine


class HasMoneyState(MachineState):
    """Concrete State - Money inserted but not enough or no item selected"""
    
    def insert_coin(self, machine: 'VendingMachine') -> None:
        print("Additional coin inserted.")
        # Stay in current state or transition based on amount
    
    def select_item(self, machine: 'VendingMachine') -> None:
        if machine.has_sufficient_money():
            print("Item selected. Payment confirmed. Dispensing item...")
            from .dispensing_state import DispensingState
            machine.set_state(DispensingState())
            machine.dispense_item()
        else:
            print("Item selected but insufficient money. Please insert more coins.")
    
    def dispense_item(self, machine: 'VendingMachine') -> None:
        print("Please select an item first.")
    
    def cancel_transaction(self, machine: 'VendingMachine') -> None:
        print("Transaction cancelled. Returning money.")
        machine.return_money()
        from .idle_state import IdleState
        machine.set_state(IdleState())