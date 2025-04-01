package atm

import (
	"sync"
)

type CashDispenser struct {
	cashAvailable int
	mu            sync.Mutex
}

func NewCashDispenser(initialCash int) *CashDispenser {
	return &CashDispenser{
		cashAvailable: initialCash,
	}
}

func (cd *CashDispenser) DispenseCash(amount int) error {
	cd.mu.Lock()
	defer cd.mu.Unlock()

	if amount > cd.cashAvailable {
		return ErrInsufficientCashInATM
	}
	cd.cashAvailable -= amount
	return nil
}
