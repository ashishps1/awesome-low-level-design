package onlineshopping

type CreditCardPayment struct{}

func (c *CreditCardPayment) ProcessPayment(amount float64) bool {
	return true
}
