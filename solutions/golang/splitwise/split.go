package splitwise

// Split is the computed result — who owes how much.
type Split struct {
	User   *User
	Amount float64
}

// SplitStrategy defines the algorithm for splitting an expense.
// To add a new split type (e.g., shares-based), implement this interface
// and register it — no existing code needs to change (Open/Closed).
type SplitStrategy interface {
	Validate(amount float64, participants []Participant) error
	Compute(amount float64, users []*User, participants []Participant) []Split
}
