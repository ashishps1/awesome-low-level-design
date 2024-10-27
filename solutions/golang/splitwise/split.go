package splitwise

type Split interface {
	GetAmount() float64
	SetAmount(amount float64)
	GetUser() *User
}
