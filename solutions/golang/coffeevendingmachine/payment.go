package coffeevendingmachine

type Payment struct {
	amount float64
}

func NewPayment(amount float64) *Payment {
	return &Payment{amount: amount}
}
