package carrentalsystem

type PaymentProcessor interface {
	ProcessPayment(amount float64) bool
}
