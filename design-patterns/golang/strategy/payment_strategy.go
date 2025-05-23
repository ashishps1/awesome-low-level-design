package strategy

// PaymentStrategy defines the interface for payment strategies
type PaymentStrategy interface {
	Pay(amount float64) string
}
