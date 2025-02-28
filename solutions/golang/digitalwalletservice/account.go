package digitalwallet

import (
	"math/big"
	"sync"
)

type Account struct {
	ID            string
	User          *User
	AccountNumber string
	Currency      Currency
	balance       *big.Float
	transactions  []*Transaction
	mu            sync.RWMutex
}

func NewAccount(id string, user *User, accountNumber string, currency Currency) *Account {
	return &Account{
		ID:            id,
		User:          user,
		AccountNumber: accountNumber,
		Currency:      currency,
		balance:       big.NewFloat(0),
		transactions:  make([]*Transaction, 0),
	}
}

func (a *Account) Deposit(amount *big.Float) {
	a.mu.Lock()
	defer a.mu.Unlock()
	a.balance.Add(a.balance, amount)
}

func (a *Account) Withdraw(amount *big.Float) error {
	a.mu.Lock()
	defer a.mu.Unlock()

	if a.balance.Cmp(amount) >= 0 {
		a.balance.Sub(a.balance, amount)
		return nil
	}
	return NewInsufficientFundsError("Insufficient funds in the account")
}

func (a *Account) AddTransaction(transaction *Transaction) {
	a.mu.Lock()
	defer a.mu.Unlock()
	a.transactions = append(a.transactions, transaction)
}

func (a *Account) GetBalance() *big.Float {
	a.mu.RLock()
	defer a.mu.RUnlock()
	return new(big.Float).Copy(a.balance)
}

func (a *Account) GetTransactions() []*Transaction {
	a.mu.RLock()
	defer a.mu.RUnlock()
	return append([]*Transaction{}, a.transactions...)
}
