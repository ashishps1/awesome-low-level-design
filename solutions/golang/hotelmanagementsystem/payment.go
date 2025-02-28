package hotelmanagement

type Payment interface {
	ProcessPayment(amount float64) bool
}

type CreditCardPayment struct{}

func NewCreditCardPayment() *CreditCardPayment {
	return &CreditCardPayment{}
}

func (p *CreditCardPayment) ProcessPayment(amount float64) bool {
	// Process credit card payment
	return true
}

type CashPayment struct{}

func NewCashPayment() *CashPayment {
	return &CashPayment{}
}

func (p *CashPayment) ProcessPayment(amount float64) bool {
	// Process cash payment
	return true
}
