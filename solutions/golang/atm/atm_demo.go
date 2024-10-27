package atm

import (
	"fmt"
)

func Run() {
	bankingService := NewBankingService()
	cashDispenser := NewCashDispenser(10000)
	atmMachine := NewATM(bankingService, cashDispenser)

	// Create sample accounts
	bankingService.CreateAccount("1234567890", 1000.0)
	bankingService.CreateAccount("9876543210", 500.0)

	// Create card and authenticate
	card := NewCard("1234567890", "1234")
	if err := atmMachine.AuthenticateUser(card); err != nil {
		fmt.Printf("Authentication failed: %v\n", err)
		return
	}

	// Check balance
	if balance, err := atmMachine.CheckBalance("1234567890"); err == nil {
		fmt.Printf("Account balance: %.2f\n", balance)
	} else {
		fmt.Printf("Error checking balance: %v\n", err)
	}

	// Withdraw cash
	if err := atmMachine.WithdrawCash("1234567890", 500.0); err == nil {
		fmt.Println("Successfully withdrew $500")
	} else {
		fmt.Printf("Error withdrawing cash: %v\n", err)
	}

	// Deposit cash
	if err := atmMachine.DepositCash("9876543210", 200.0); err == nil {
		fmt.Println("Successfully deposited $200")
	} else {
		fmt.Printf("Error depositing cash: %v\n", err)
	}

	// Check updated balance
	if balance, err := atmMachine.CheckBalance("1234567890"); err == nil {
		fmt.Printf("Updated account balance: %.2f\n", balance)
	} else {
		fmt.Printf("Error checking balance: %v\n", err)
	}
}
