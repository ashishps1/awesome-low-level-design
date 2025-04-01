package splitwise

type Group struct {
	ID       string
	Name     string
	Members  []*User
	Expenses []*Expense
}

func NewGroup(id, name string) *Group {
	return &Group{
		ID:       id,
		Name:     name,
		Members:  []*User{},
		Expenses: []*Expense{},
	}
}

func (g *Group) AddMember(user *User) {
	g.Members = append(g.Members, user)
}

func (g *Group) AddExpense(expense *Expense) {
	g.Expenses = append(g.Expenses, expense)
}
