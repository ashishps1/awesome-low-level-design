package splitwise

import "fmt"

type Group struct {
	ID       string
	Name     string
	members  map[string]*User
	expenses []*Expense
}

func NewGroup(id, name string) *Group {
	return &Group{
		ID:      id,
		Name:    name,
		members: make(map[string]*User),
	}
}

func (g *Group) AddMember(user *User) {
	g.members[user.ID] = user
}

func (g *Group) IsMember(userID string) bool {
	_, ok := g.members[userID]
	return ok
}

func (g *Group) AddExpense(expense *Expense) error {
	if !g.IsMember(expense.PaidBy.ID) {
		return fmt.Errorf("payer %s is not a member of group %s", expense.PaidBy.Name, g.Name)
	}
	for _, s := range expense.Splits {
		if !g.IsMember(s.User.ID) {
			return fmt.Errorf("user %s is not a member of group %s", s.User.Name, g.Name)
		}
	}
	g.expenses = append(g.expenses, expense)
	return nil
}

func (g *Group) GetExpenses() []*Expense {
	return g.expenses
}

func (g *Group) GetMembers() map[string]*User {
	return g.members
}
