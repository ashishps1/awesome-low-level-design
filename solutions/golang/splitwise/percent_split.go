package splitwise

type PercentSplit struct {
	User    *User
	Amount  float64
	Percent float64
}

func NewPercentSplit(user *User, percent float64) *PercentSplit {
	return &PercentSplit{User: user, Percent: percent}
}

func (p *PercentSplit) GetAmount() float64 {
	return p.Amount
}

func (p *PercentSplit) SetAmount(amount float64) {
	p.Amount = amount
}

func (p *PercentSplit) GetUser() *User {
	return p.User
}
