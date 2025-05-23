package adapter

import (
	"fmt"
	"time"
)

// InHousePaymentProcessor represents our in-house payment processing system
type InHousePaymentProcessor struct {
	transactionID string
	isSuccessful  bool
}

// ProcessPayment implements the PaymentProcessor interface
func (p *InHousePaymentProcessor) ProcessPayment(amount float64, currency string) {
	fmt.Printf("InHousePaymentProcessor: Processing payment of %s %.2f\n", currency, amount)
	p.transactionID = fmt.Sprintf("INH-%d", time.Now().UnixNano())
	p.isSuccessful = true
	fmt.Printf("InHousePaymentProcessor: Payment processed successfully. Txn ID: %s\n", p.transactionID)
}

// IsPaymentSuccessful implements the PaymentProcessor interface
func (p *InHousePaymentProcessor) IsPaymentSuccessful() bool {
	return p.isSuccessful
}

// GetTransactionID implements the PaymentProcessor interface
func (p *InHousePaymentProcessor) GetTransactionID() string {
	return p.transactionID
}
