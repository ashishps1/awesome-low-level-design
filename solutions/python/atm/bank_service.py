from typing import Dict, Optional
from account import Account
from card import Card

class BankService:
    def __init__(self):
        self._accounts: Dict[str, Account] = {}
        self._cards: Dict[str, Card] = {}
        self._card_account_map: Dict[Card, Account] = {}
        
        # Create sample accounts and cards
        account1 = self.create_account("1234567890", 1000.0)
        card1 = self.create_card("1234-5678-9012-3456", "1234")
        self.link_card_to_account(card1, account1)
        
        account2 = self.create_account("9876543210", 500.0)
        card2 = self.create_card("9876-5432-1098-7654", "4321")
        self.link_card_to_account(card2, account2)
    
    def create_account(self, account_number: str, initial_balance: float) -> Account:
        account = Account(account_number, initial_balance)
        self._accounts[account_number] = account
        return account
    
    def create_card(self, card_number: str, pin: str) -> Card:
        card = Card(card_number, pin)
        self._cards[card_number] = card
        return card
    
    def authenticate(self, card: Card, pin: str) -> bool:
        return card.get_pin() == pin
    
    def authenticate_card(self, card_number: str) -> Optional[Card]:
        return self._cards.get(card_number)
    
    def get_balance(self, card: Card) -> float:
        return self._card_account_map[card].get_balance()
    
    def withdraw_money(self, card: Card, amount: float):
        self._card_account_map[card].withdraw(amount)
    
    def deposit_money(self, card: Card, amount: float):
        self._card_account_map[card].deposit(amount)
    
    def link_card_to_account(self, card: Card, account: Account):
        account.get_cards()[card.get_card_number()] = card
        self._card_account_map[card] = account