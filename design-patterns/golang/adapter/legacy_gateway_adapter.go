package adapter

import "fmt"

// LegacyGatewayAdapter adapts the LegacyGateway to the PaymentProcessor interface
type LegacyGatewayAdapter struct {
	legacyGateway *LegacyGateway
}

// NewLegacyGatewayAdapter creates a new LegacyGatewayAdapter
func NewLegacyGatewayAdapter(legacyGateway *LegacyGateway) *LegacyGatewayAdapter {
	return &LegacyGatewayAdapter{
		legacyGateway: legacyGateway,
	}
}

// ProcessPayment implements the PaymentProcessor interface
func (adapter *LegacyGatewayAdapter) ProcessPayment(amount float64, currency string) {
	adapter.legacyGateway.ExecuteTransaction(amount, currency)
}

// IsPaymentSuccessful implements the PaymentProcessor interface
func (adapter *LegacyGatewayAdapter) IsPaymentSuccessful() bool {
	return adapter.legacyGateway.CheckStatus(adapter.legacyGateway.GetReferenceNumber())
}

// GetTransactionID implements the PaymentProcessor interface
func (adapter *LegacyGatewayAdapter) GetTransactionID() string {
	return fmt.Sprintf("LEG-%d", adapter.legacyGateway.GetReferenceNumber())
}
