package strategy

func main() {
	cart := NewShoppingCart(100.0)

	// Use credit card payment
	creditCard := NewCreditCardPayment("1234-5678-9012-3456", "John Doe", "123", "12/25")
	cart.SetPaymentStrategy(creditCard)
	cart.Checkout()

	// Use PayPal payment
	paypal := NewPayPalPayment("john@example.com")
	cart.SetPaymentStrategy(paypal)
	cart.Checkout()
} 