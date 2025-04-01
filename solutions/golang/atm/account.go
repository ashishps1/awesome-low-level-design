package atm

import "sync"

type Account struct {
	accountNumber string
	balance       float64
	mu            sync.Mutex
}

func NewAccount(accountNumber string, balance float64) *Account {
	return &Account{
		accountNumber: accountNumber,
		balance:       balance,
	}
}

func (a *Account) GetAccountNumber() string {
	return a.accountNumber
}

func (a *Account) GetBalance() float64 {
	a.mu.Lock()
	defer a.mu.Unlock()
	return a.balance
}

func (a *Account) Debit(amount float64) error {
	a.mu.Lock()
	defer a.mu.Unlock()
	if a.balance < amount {
		return ErrInsufficientFunds
	}
	a.balance -= amount
	return nil
}

func (a *Account) Credit(amount float64) error {
	a.mu.Lock()
	defer a.mu.Unlock()
	a.balance += amount
	return nil
}
