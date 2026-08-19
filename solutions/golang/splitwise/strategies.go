package splitwise

import (
	"fmt"
	"math"
)

// --- EqualStrategy ---

type EqualStrategy struct{}

func NewEqualStrategy() SplitStrategy {
	return &EqualStrategy{}
}

func (*EqualStrategy) Validate(_ float64, participants []Participant) error {
	if len(participants) == 0 {
		return fmt.Errorf("must have at least one participant")
	}
	return nil
}

func (*EqualStrategy) Compute(amount float64, users []*User, _ []Participant) []Split {
	share := amount / float64(len(users))
	splits := make([]Split, len(users))
	for i, u := range users {
		splits[i] = Split{User: u, Amount: share}
	}
	return splits
}

// --- PercentStrategy ---

type PercentStrategy struct{}

func NewPercentStrategy() SplitStrategy {
	return &PercentStrategy{}
}

func (*PercentStrategy) Validate(_ float64, participants []Participant) error {
	var total float64
	for _, p := range participants {
		total += p.Value
	}
	if math.Abs(total-100.0) > 0.01 {
		return fmt.Errorf("percent shares must sum to 100, got %.2f", total)
	}
	return nil
}

func (*PercentStrategy) Compute(amount float64, users []*User, participants []Participant) []Split {
	splits := make([]Split, len(users))
	for i, p := range participants {
		splits[i] = Split{User: users[i], Amount: amount * p.Value / 100.0}
	}
	return splits
}

// --- ExactStrategy ---

type ExactStrategy struct{}

func NewExactStrategy() SplitStrategy {
	return &ExactStrategy{}
}

func (*ExactStrategy) Validate(amount float64, participants []Participant) error {
	var total float64
	for _, p := range participants {
		total += p.Value
	}
	if math.Abs(total-amount) > 0.01 {
		return fmt.Errorf("exact shares must sum to %.2f, got %.2f", amount, total)
	}
	return nil
}

func (*ExactStrategy) Compute(_ float64, users []*User, participants []Participant) []Split {
	splits := make([]Split, len(users))
	for i, p := range participants {
		splits[i] = Split{User: users[i], Amount: p.Value}
	}
	return splits
}

// --- Strategy Registry ---
// Maps ExpenseType to its strategy. To add a new split type,
// just implement SplitStrategy and add one line here.

var strategyRegistry = map[ExpenseType]SplitStrategy{
	Equal:   NewEqualStrategy(),
	Percent: NewPercentStrategy(),
	Exact:   NewExactStrategy(),
}
