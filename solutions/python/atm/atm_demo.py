from atm import ATM
from banking_service import BankingService
from cash_dispenser import CashDispenser
from card import Card

class ATMDemo:
    @staticmethod
    def run():
        banking_service = BankingService()
        cash_dispenser = CashDispenser(10000)
        atm = ATM(banking_service, cash_dispenser)

        # Create sample accounts
        banking_service.create_account("1234567890", 1000.0)
        banking_service.create_account("9876543210", 500.0)

        # Perform ATM operations
        card = Card("1234567890", "1234")
        atm.authenticate_user(card)

        balance = atm.check_balance("1234567890")
        print("Account balance:", balance)

        atm.withdraw_cash("1234567890", 500.0)
        atm.deposit_cash("9876543210", 200.0)

        balance = atm.check_balance("1234567890")
        print("Updated account balance:", balance)

if __name__ == "__main__":
    ATMDemo.run()