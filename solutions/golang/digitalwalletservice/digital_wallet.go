package digitalwallet

import (
	"fmt"
	"math/big"
	"sync"
	"time"
)

type DigitalWallet struct {
	users          map[string]*User
	accounts       map[string]*Account
	paymentMethods map[string]PaymentMethod
	mu             sync.RWMutex
}

var (
	instance *DigitalWallet
	once     sync.Once
)

func GetDigitalWallet() *DigitalWallet {
	once.Do(func() {
		instance = &DigitalWallet{
			users:          make(map[string]*User),
			accounts:       make(map[string]*Account),
			paymentMethods: make(map[string]PaymentMethod),
		}
	})
	return instance
}

func (dw *DigitalWallet) CreateUser(user *User) {
	dw.mu.Lock()
	defer dw.mu.Unlock()
	dw.users[user.ID] = user
}

func (dw *DigitalWallet) CreateAccount(account *Account) {
	dw.mu.Lock()
	defer dw.mu.Unlock()
	dw.accounts[account.ID] = account
	account.User.AddAccount(account)
}

func (dw *DigitalWallet) AddPaymentMethod(method PaymentMethod) {
	dw.mu.Lock()
	defer dw.mu.Unlock()
	dw.paymentMethods[method.GetID()] = method
}

func (dw *DigitalWallet) TransferFunds(sourceAccount, destinationAccount *Account, amount *big.Float, currency Currency) error {
	dw.mu.Lock()
	defer dw.mu.Unlock()

	converter := GetCurrencyConverter()

	// Convert amount to source account currency
	sourceAmount := amount
	if sourceAccount.Currency != currency {
		sourceAmount = converter.Convert(amount, currency, sourceAccount.Currency)
	}

	// Withdraw from source account
	if err := sourceAccount.Withdraw(sourceAmount); err != nil {
		return err
	}

	// Convert amount to destination account currency
	destAmount := amount
	if destinationAccount.Currency != currency {
		destAmount = converter.Convert(amount, currency, destinationAccount.Currency)
	}

	// Deposit to destination account
	destinationAccount.Deposit(destAmount)

	// Create and record transaction
	transactionID := fmt.Sprintf("TXN%d", time.Now().UnixNano())
	transaction := NewTransaction(transactionID, sourceAccount, destinationAccount, amount, currency)
	sourceAccount.AddTransaction(transaction)
	destinationAccount.AddTransaction(transaction)

	return nil
}

func (dw *DigitalWallet) GetTransactionHistory(account *Account) []*Transaction {
	return account.GetTransactions()
}
