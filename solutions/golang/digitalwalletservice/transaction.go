package digitalwallet

import (
	"math/big"
	"time"
)

type Transaction struct {
	ID                 string
	SourceAccount      *Account
	DestinationAccount *Account
	Amount             *big.Float
	Currency           Currency
	Timestamp          time.Time
}

func NewTransaction(id string, sourceAccount, destinationAccount *Account, amount *big.Float, currency Currency) *Transaction {
	return &Transaction{
		ID:                 id,
		SourceAccount:      sourceAccount,
		DestinationAccount: destinationAccount,
		Amount:             amount,
		Currency:           currency,
		Timestamp:          time.Now(),
	}
}
