package splitwise

type EqualSplit struct {
	User   *User
	Amount float64
}

func NewEqualSplit(user *User) *EqualSplit {
	return &EqualSplit{User: user}
}

func (e *EqualSplit) GetAmount() float64 {
	return e.Amount
}

func (e *EqualSplit) SetAmount(amount float64) {
	e.Amount = amount
}

func (e *EqualSplit) GetUser() *User {
	return e.User
}
