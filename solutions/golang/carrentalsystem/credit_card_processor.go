package carrentalsystem

type CreditCardPaymentProcessor struct{}

func NewCreditCardPaymentProcessor() *CreditCardPaymentProcessor {
	return &CreditCardPaymentProcessor{}
}

func (p *CreditCardPaymentProcessor) ProcessPayment(amount float64) bool {
	// Process credit card payment
	return true
}
