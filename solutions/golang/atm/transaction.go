package atm

type Transaction interface {
	Execute() error
}

type BaseTransaction struct {
	TransactionID string
	Account       *Account
	Amount        float64
}
