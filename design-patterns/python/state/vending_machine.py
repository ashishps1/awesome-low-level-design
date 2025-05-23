from .machine_state import MachineState
from .idle_state import IdleState


class VendingMachine:
    """Context - Vending machine that changes behavior based on state"""
    
    def __init__(self):
        self._state: MachineState = IdleState()
        self._money_inserted = 0.0
        self._item_price = 1.50  # Price for items
    
    def set_state(self, state: MachineState) -> None:
        self._state = state
    
    def insert_coin(self, amount: float = 1.0) -> None:
        self._money_inserted += amount
        print(f"${amount:.2f} inserted. Total: ${self._money_inserted:.2f}")
        self._state.insert_coin(self)
    
    def select_item(self) -> None:
        self._state.select_item(self)
    
    def dispense_item(self) -> None:
        self._state.dispense_item(self)
        if self._money_inserted >= self._item_price:
            self._money_inserted -= self._item_price
            if self._money_inserted > 0:
                print(f"Change returned: ${self._money_inserted:.2f}")
                self._money_inserted = 0.0
    
    def cancel_transaction(self) -> None:
        self._state.cancel_transaction(self)
    
    def has_sufficient_money(self) -> bool:
        return self._money_inserted >= self._item_price
    
    def return_money(self) -> None:
        if self._money_inserted > 0:
            print(f"Returning ${self._money_inserted:.2f}")
            self._money_inserted = 0.0
    
    @property
    def current_state(self) -> str:
        return self._state.__class__.__name__
    
    @property
    def money_inserted(self) -> float:
        return self._money_inserted