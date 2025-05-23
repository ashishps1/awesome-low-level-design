package adapter

// PaymentProcessor defines the interface for processing payments
type PaymentProcessor interface {
	ProcessPayment(amount float64, currency string)
	IsPaymentSuccessful() bool
	GetTransactionID() string
}
