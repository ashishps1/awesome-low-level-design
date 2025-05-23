package adapter

import "fmt"

// CheckoutService handles the checkout process
type CheckoutService struct {
	paymentProcessor PaymentProcessor
}

// NewCheckoutService creates a new CheckoutService
func NewCheckoutService(paymentProcessor PaymentProcessor) *CheckoutService {
	return &CheckoutService{
		paymentProcessor: paymentProcessor,
	}
}

// ProcessCheckout processes a checkout with the given amount and currency
func (cs *CheckoutService) ProcessCheckout(amount float64, currency string) {
	cs.paymentProcessor.ProcessPayment(amount, currency)

	if cs.paymentProcessor.IsPaymentSuccessful() {
		fmt.Printf("Checkout successful! Transaction ID: %s\n", cs.paymentProcessor.GetTransactionID())
	} else {
		fmt.Println("Checkout failed!")
	}
}
