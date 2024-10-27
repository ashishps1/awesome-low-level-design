package splitwise

type Expense struct {
	ID          string
	Amount      float64
	Description string
	PaidBy      *User
	Splits      []Split
}

func NewExpense(id string, amount float64, description string, paidBy *User) *Expense {
	return &Expense{
		ID:          id,
		Amount:      amount,
		Description: description,
		PaidBy:      paidBy,
		Splits:      []Split{},
	}
}

func (e *Expense) AddSplit(split Split) {
	e.Splits = append(e.Splits, split)
}
