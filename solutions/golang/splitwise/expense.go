package splitwise

import "fmt"

type ExpenseType int

const (
	Equal ExpenseType = iota
	Percent
	Exact
)

// Participant is the API-friendly input: a user ID + an optional value.
// For Equal:   Value is ignored.
// For Percent: Value is the percentage share.
// For Exact:   Value is the exact dollar amount.
type Participant struct {
	UserID string
	Value  float64
}

type Expense struct {
	ID          string
	Description string
	Amount      float64
	PaidBy      *User
	Splits      []Split
	Type        ExpenseType
}

// NewExpense creates an expense by looking up the strategy from the registry.
// No switch — adding a new split type only requires a new SplitStrategy
// implementation and one registry entry.
func NewExpense(id string, amount float64, desc string, paidBy *User, expType ExpenseType, participants []Participant, userLookup func(string) (*User, bool)) (*Expense, error) {
	if amount <= 0 {
		return nil, fmt.Errorf("expense amount must be positive")
	}
	if len(participants) == 0 {
		return nil, fmt.Errorf("expense must have at least one participant")
	}

	strategy, ok := strategyRegistry[expType]
	if !ok {
		return nil, fmt.Errorf("unknown expense type: %d", expType)
	}

	if err := strategy.Validate(amount, participants); err != nil {
		return nil, err
	}

	users := make([]*User, len(participants))
	for i, p := range participants {
		u, found := userLookup(p.UserID)
		if !found {
			return nil, fmt.Errorf("user %s not found", p.UserID)
		}
		users[i] = u
	}

	splits := strategy.Compute(amount, users, participants)

	return &Expense{
		ID: id, Description: desc, Amount: amount,
		PaidBy: paidBy, Splits: splits, Type: expType,
	}, nil
}
