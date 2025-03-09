from decimal import Decimal
from user import User
from account import Account
from currency import Currency
from digital_wallet import DigitalWallet
from credit_card import CreditCard
from bank_account import BankAccount

class DigitalWalletDemo:
    @staticmethod
    def run():
        digital_wallet = DigitalWallet.get_instance()

        # Create users
        user1 = User("U001", "John Doe", "john@example.com", "password123")
        user2 = User("U002", "Jane Smith", "jane@example.com", "password456")
        digital_wallet.create_user(user1)
        digital_wallet.create_user(user2)

        # Create accounts
        account1 = Account("A001", user1, "1234567890", Currency.USD)
        account2 = Account("A002", user2, "9876543210", Currency.EUR)
        digital_wallet.create_account(account1)
        digital_wallet.create_account(account2)

        # Add payment methods
        credit_card = CreditCard("PM001", user1, "1234567890123456", "12/25", "123")
        bank_account = BankAccount("PM002", user2, "9876543210", "987654321")
        digital_wallet.add_payment_method(credit_card)
        digital_wallet.add_payment_method(bank_account)

        # Deposit funds
        account1.deposit(Decimal("1000.00"))
        account2.deposit(Decimal("500.00"))

        # Transfer funds
        digital_wallet.transfer_funds(account1, account2, Decimal("100.00"), Currency.USD)

        # Get transaction history
        transaction_history1 = digital_wallet.get_transaction_history(account1)
        transaction_history2 = digital_wallet.get_transaction_history(account2)

        # Print transaction history
        print("Transaction History for Account 1:")
        for transaction in transaction_history1:
            print(f"Transaction ID: {transaction.id}")
            print(f"Amount: {transaction.amount} {transaction.currency}")
            print(f"Timestamp: {transaction.timestamp}")
            print()

        print("Transaction History for Account 2:")
        for transaction in transaction_history2:
            print(f"Transaction ID: {transaction.id}")
            print(f"Amount: {transaction.amount} {transaction.currency}")
            print(f"Timestamp: {transaction.timestamp}")
            print()

if __name__ == "__main__":
    DigitalWalletDemo.run()