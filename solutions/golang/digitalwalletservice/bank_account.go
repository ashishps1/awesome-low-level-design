package digitalwallet

import "math/big"

type BankAccount struct {
	BasePaymentMethod
	AccountNumber string
	RoutingNumber string
}

func NewBankAccount(id string, user *User, accountNumber, routingNumber string) *BankAccount {
	return &BankAccount{
		BasePaymentMethod: BasePaymentMethod{ID: id, User: user},
		AccountNumber:     accountNumber,
		RoutingNumber:     routingNumber,
	}
}

func (b *BankAccount) ProcessPayment(amount *big.Float, currency Currency) bool {
	// Process bank account payment
	return true
}
