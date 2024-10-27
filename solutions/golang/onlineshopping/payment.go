package onlineshopping

type Payment interface {
	ProcessPayment(amount float64) bool
}
