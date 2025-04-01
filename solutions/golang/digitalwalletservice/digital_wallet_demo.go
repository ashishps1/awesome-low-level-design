package digitalwallet

import (
	"fmt"
	"math/big"
)

func Run() {
	digitalWallet := GetDigitalWallet()

	// Create users
	user1 := NewUser("U001", "John Doe", "john@example.com", "password123")
	user2 := NewUser("U002", "Jane Smith", "jane@example.com", "password456")
	digitalWallet.CreateUser(user1)
	digitalWallet.CreateUser(user2)

	// Create accounts
	account1 := NewAccount("A001", user1, "1234567890", USD)
	account2 := NewAccount("A002", user2, "9876543210", EUR)
	digitalWallet.CreateAccount(account1)
	digitalWallet.CreateAccount(account2)

	// Add payment methods
	creditCard := NewCreditCard("PM001", user1, "1234567890123456", "12/25", "123")
	bankAccount := NewBankAccount("PM002", user2, "9876543210", "987654321")
	digitalWallet.AddPaymentMethod(creditCard)
	digitalWallet.AddPaymentMethod(bankAccount)

	// Deposit funds
	account1.Deposit(big.NewFloat(1000.00))
	account2.Deposit(big.NewFloat(500.00))

	// Transfer funds
	amount := big.NewFloat(100.00)
	if err := digitalWallet.TransferFunds(account1, account2, amount, USD); err != nil {
		fmt.Printf("Transfer failed: %v\n", err)
	}

	// Print transaction history
	fmt.Println("Transaction History for Account 1:")
	for _, transaction := range digitalWallet.GetTransactionHistory(account1) {
		fmt.Printf("Transaction ID: %s\n", transaction.ID)
		fmt.Printf("Amount: %v %s\n", transaction.Amount, transaction.Currency)
		fmt.Printf("Timestamp: %v\n\n", transaction.Timestamp)
	}

	fmt.Println("Transaction History for Account 2:")
	for _, transaction := range digitalWallet.GetTransactionHistory(account2) {
		fmt.Printf("Transaction ID: %s\n", transaction.ID)
		fmt.Printf("Amount: %v %s\n", transaction.Amount, transaction.Currency)
		fmt.Printf("Timestamp: %v\n\n", transaction.Timestamp)
	}
}
