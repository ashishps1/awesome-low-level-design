package digitalwallet

import "math/big"

type CreditCard struct {
	BasePaymentMethod
	CardNumber     string
	ExpirationDate string
	CVV            string
}

func NewCreditCard(id string, user *User, cardNumber, expirationDate, cvv string) *CreditCard {
	return &CreditCard{
		BasePaymentMethod: BasePaymentMethod{ID: id, User: user},
		CardNumber:        cardNumber,
		ExpirationDate:    expirationDate,
		CVV:               cvv,
	}
}

func (c *CreditCard) ProcessPayment(amount *big.Float, currency Currency) bool {
	// Process credit card payment
	return true
}
