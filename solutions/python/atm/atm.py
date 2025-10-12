import threading
from typing import Optional
from atm_state import ATMState, IdleState
from bank_service import BankService
from card import Card
from operation_type import OperationType
from note_dispenser import NoteDispenser100, NoteDispenser50, NoteDispenser20
from cash_dispenser import CashDispenser

class ATM:
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
            self._current_state = IdleState()
            self._bank_service = BankService()
            self._current_card: Optional[Card] = None
            self._transaction_counter = 0
            
            # Setup the dispenser chain
            c1 = NoteDispenser100(10)  # 10 x $100 notes
            c2 = NoteDispenser50(20)   # 20 x $50 notes
            c3 = NoteDispenser20(30)   # 30 x $20 notes
            c1.set_next_chain(c2)
            c2.set_next_chain(c3)
            self._cash_dispenser = CashDispenser(c1)
            self._initialized = True
    
    @classmethod
    def get_instance(cls):
        return cls()
    
    def change_state(self, new_state: ATMState):
        self._current_state = new_state
    
    def set_current_card(self, card: Optional[Card]):
        self._current_card = card
    
    def insert_card(self, card_number: str):
        self._current_state.insert_card(self, card_number)
    
    def enter_pin(self, pin: str):
        self._current_state.enter_pin(self, pin)
    
    def select_operation(self, op: OperationType, *args):
        self._current_state.select_operation(self, op, *args)
    
    def check_balance(self):
        balance = self._bank_service.get_balance(self._current_card)
        print(f"Your current account balance is: ${balance:.2f}")
    
    def withdraw_cash(self, amount: int):
        if not self._cash_dispenser.can_dispense_cash(amount):
            raise RuntimeError("Insufficient cash available in the ATM.")
        
        self._bank_service.withdraw_money(self._current_card, amount)
        
        try:
            self._cash_dispenser.dispense_cash(amount)
        except Exception as e:
            self._bank_service.deposit_money(self._current_card, amount)  # Deposit back if dispensing fails
            raise e
    
    def deposit_cash(self, amount: int):
        self._bank_service.deposit_money(self._current_card, amount)
    
    def get_current_card(self) -> Optional[Card]:
        return self._current_card
    
    def get_bank_service(self) -> BankService:
        return self._bank_service