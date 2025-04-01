package digitalwallet

import "math/big"

type PaymentMethod interface {
	ProcessPayment(amount *big.Float, currency Currency) bool
	GetID() string
	GetUser() *User
}

type BasePaymentMethod struct {
	ID   string
	User *User
}

func (b *BasePaymentMethod) GetID() string {
	return b.ID
}

func (b *BasePaymentMethod) GetUser() *User {
	return b.User
}
