package adapter

import (
	"fmt"
	"time"
)

// LegacyGateway represents the legacy payment gateway
type LegacyGateway struct {
	transactionReference int64
	isPaymentSuccessful  bool
}

// ExecuteTransaction processes a payment using the legacy gateway
func (lg *LegacyGateway) ExecuteTransaction(totalAmount float64, currency string) {
	fmt.Printf("LegacyGateway: Executing transaction for %s %.2f\n", currency, totalAmount)
	lg.transactionReference = time.Now().UnixNano()
	lg.isPaymentSuccessful = true
	fmt.Printf("LegacyGateway: Transaction executed successfully. Txn ID: %d\n", lg.transactionReference)
}

// CheckStatus checks the status of a transaction
func (lg *LegacyGateway) CheckStatus(transactionReference int64) bool {
	fmt.Printf("LegacyGateway: Checking status for ref: %d\n", transactionReference)
	return lg.isPaymentSuccessful
}

// GetReferenceNumber returns the transaction reference number
func (lg *LegacyGateway) GetReferenceNumber() int64 {
	return lg.transactionReference
}
