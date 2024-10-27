package carrentalsystem

type PayPalPaymentProcessor struct{}

func NewPayPalPaymentProcessor() *PayPalPaymentProcessor {
	return &PayPalPaymentProcessor{}
}

func (p *PayPalPaymentProcessor) ProcessPayment(amount float64) bool {
	// Process PayPal payment
	return true
}
