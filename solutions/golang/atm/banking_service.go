package atm

import (
	"sync"
)

type BankingService struct {
	accounts map[string]*Account
	mu       sync.RWMutex
}

func NewBankingService() *BankingService {
	return &BankingService{
		accounts: make(map[string]*Account),
	}
}

func (bs *BankingService) CreateAccount(accountNumber string, initialBalance float64) {
	bs.mu.Lock()
	defer bs.mu.Unlock()
	bs.accounts[accountNumber] = NewAccount(accountNumber, initialBalance)
}

func (bs *BankingService) GetAccount(accountNumber string) *Account {
	bs.mu.RLock()
	defer bs.mu.RUnlock()
	return bs.accounts[accountNumber]
}

func (bs *BankingService) ProcessTransaction(transaction Transaction) error {
	return transaction.Execute()
}
