from .machine_state import MachineState
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from .vending_machine import VendingMachine


class ItemSelectedState(MachineState):
    """Concrete State - Item has been selected, ready to check money"""
    
    def insert_coin(self, machine: 'VendingMachine') -> None:
        print("Coin already inserted. Please select an item.")
    
    def select_item(self, machine: 'VendingMachine') -> None:
        print("Item selected. Checking if sufficient money...")
        if machine.has_sufficient_money():
            print("Payment confirmed. Dispensing item...")
            from .dispensing_state import DispensingState
            machine.set_state(DispensingState())
            machine.dispense_item()
        else:
            print("Insufficient money. Please insert more coins.")
            from .has_money_state import HasMoneyState
            machine.set_state(HasMoneyState())
    
    def dispense_item(self, machine: 'VendingMachine') -> None:
        print("Please select an item first.")
    
    def cancel_transaction(self, machine: 'VendingMachine') -> None:
        print("Transaction cancelled. Returning money.")
        machine.return_money()
        from .idle_state import IdleState
        machine.set_state(IdleState())