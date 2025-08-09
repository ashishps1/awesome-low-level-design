from abc import ABC, abstractmethod
from operation_type import OperationType
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from atm import ATM

class ATMState(ABC):
    @abstractmethod
    def insert_card(self, atm: 'ATM', card_number: str):
        pass
    
    @abstractmethod
    def enter_pin(self, atm: 'ATM', pin: str):
        pass
    
    @abstractmethod
    def select_operation(self, atm: 'ATM', op: OperationType, *args):
        pass
    
    @abstractmethod
    def eject_card(self, atm: 'ATM'):
        pass

class IdleState(ATMState):
    def insert_card(self, atm: 'ATM', card_number: str):
        print("\nCard has been inserted.")
        card = atm.get_bank_service().authenticate_card(card_number)
        
        if card is None:
            self.eject_card(atm)
        else:
            atm.set_current_card(card)
            atm.change_state(HasCardState())
    
    def enter_pin(self, atm: 'ATM', pin: str):
        print("Error: Please insert a card first.")
    
    def select_operation(self, atm: 'ATM', op: OperationType, *args):
        print("Error: Please insert a card first.")
    
    def eject_card(self, atm: 'ATM'):
        print("Error: Card not found.")

class HasCardState(ATMState):
    def insert_card(self, atm: 'ATM', card_number: str):
        print("Error: A card is already inserted. Cannot insert another card.")
    
    def enter_pin(self, atm: 'ATM', pin: str):
        print("Authenticating PIN...")
        card = atm.get_current_card()
        is_authenticated = atm.get_bank_service().authenticate(card, pin)
        
        if is_authenticated:
            print("Authentication successful.")
            atm.change_state(AuthenticatedState())
        else:
            print("Authentication failed: Incorrect PIN.")
            self.eject_card(atm)
    
    def select_operation(self, atm: 'ATM', op: OperationType, *args):
        print("Error: Please enter your PIN first to select an operation.")
    
    def eject_card(self, atm: 'ATM'):
        print("Card has been ejected. Thank you for using our ATM.")
        atm.set_current_card(None)
        atm.change_state(IdleState())

class AuthenticatedState(ATMState):
    def insert_card(self, atm: 'ATM', card_number: str):
        print("Error: A card is already inserted and a session is active.")
    
    def enter_pin(self, atm: 'ATM', pin: str):
        print("Error: PIN has already been entered and authenticated.")
    
    def select_operation(self, atm: 'ATM', op: OperationType, *args):
        if op == OperationType.CHECK_BALANCE:
            atm.check_balance()
        elif op == OperationType.WITHDRAW_CASH:
            if len(args) == 0 or args[0] <= 0:
                print("Error: Invalid withdrawal amount specified.")
                return
            
            amount_to_withdraw = args[0]
            account_balance = atm.get_bank_service().get_balance(atm.get_current_card())
            
            if amount_to_withdraw > account_balance:
                print("Error: Insufficient balance.")
                return
            
            print(f"Processing withdrawal for ${amount_to_withdraw}")
            atm.withdraw_cash(amount_to_withdraw)
        elif op == OperationType.DEPOSIT_CASH:
            if len(args) == 0 or args[0] <= 0:
                print("Error: Invalid deposit amount specified.")
                return
            
            amount_to_deposit = args[0]
            print(f"Processing deposit for ${amount_to_deposit}")
            atm.deposit_cash(amount_to_deposit)
        else:
            print("Error: Invalid operation selected.")
            return
        
        # End the session after one transaction
        print("Transaction complete.")
        self.eject_card(atm)
    
    def eject_card(self, atm: 'ATM'):
        print("Ending session. Card has been ejected. Thank you for using our ATM.")
        atm.set_current_card(None)
        atm.change_state(IdleState())