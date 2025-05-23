package strategy

import "fmt"

// PayPalPayment represents the PayPal payment strategy
type PayPalPayment struct {
	email string
}

// NewPayPalPayment creates a new PayPal payment strategy
func NewPayPalPayment(email string) *PayPalPayment {
	return &PayPalPayment{email: email}
}

// Pay implements the payment strategy for PayPal
func (p *PayPalPayment) Pay(amount float64) string {
	return fmt.Sprintf("%.2f paid using PayPal", amount)
}
