package onlinestockbrokeragesystem

import "sync"

type Account struct {
	AccountID string
	User      *User
	balance   float64
	Portfolio *Portfolio
	mu        sync.RWMutex
}

func NewAccount(accountID string, user *User, initialBalance float64) *Account {
	account := &Account{
		AccountID: accountID,
		User:      user,
		balance:   initialBalance,
	}
	account.Portfolio = NewPortfolio(account)
	return account
}

func (a *Account) Deposit(amount float64) {
	a.mu.Lock()
	defer a.mu.Unlock()
	a.balance += amount
}

func (a *Account) Withdraw(amount float64) error {
	a.mu.Lock()
	defer a.mu.Unlock()

	if a.balance < amount {
		return NewInsufficientFundsError("insufficient funds in account")
	}

	a.balance -= amount
	return nil
}

func (a *Account) GetBalance() float64 {
	a.mu.RLock()
	defer a.mu.RUnlock()
	return a.balance
}
