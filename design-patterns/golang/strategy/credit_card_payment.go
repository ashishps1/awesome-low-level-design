package strategy

import "fmt"

// CreditCardPayment represents the credit card payment strategy
type CreditCardPayment struct {
	cardNumber string
	name       string
	cvv        string
	dateOfExp  string
}

// NewCreditCardPayment creates a new credit card payment strategy
func NewCreditCardPayment(cardNumber, name, cvv, dateOfExp string) *CreditCardPayment {
	return &CreditCardPayment{
		cardNumber: cardNumber,
		name:       name,
		cvv:        cvv,
		dateOfExp:  dateOfExp,
	}
}

// Pay implements the payment strategy for credit card
func (c *CreditCardPayment) Pay(amount float64) string {
	return fmt.Sprintf("%.2f paid with credit/debit card", amount)
}
