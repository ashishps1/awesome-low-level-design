package splitwise

import (
	"fmt"
	"sync"
)

// Singleton Pattern: thread-safe single instance via sync.Once

type SplitwiseService struct {
	mu           sync.RWMutex
	users        map[string]*User
	groups       map[string]*Group
	balances     map[string]map[string]float64 // balances[A][B] > 0 means B owes A
	transactions []*Transaction
	txCounter    int
}

var (
	instance *SplitwiseService
	once     sync.Once
)

func GetService() *SplitwiseService {
	once.Do(func() {
		instance = &SplitwiseService{
			users:    make(map[string]*User),
			groups:   make(map[string]*Group),
			balances: make(map[string]map[string]float64),
		}
	})
	return instance
}

// ResetService allows resetting for tests
func ResetService() {
	once = sync.Once{}
	instance = nil
}

func (s *SplitwiseService) AddUser(user *User) {
	s.mu.Lock()
	defer s.mu.Unlock()
	s.users[user.ID] = user
	s.balances[user.ID] = make(map[string]float64)
}

func (s *SplitwiseService) GetUser(id string) (*User, bool) {
	s.mu.RLock()
	defer s.mu.RUnlock()
	u, ok := s.users[id]
	return u, ok
}

func (s *SplitwiseService) AddGroup(group *Group) {
	s.mu.Lock()
	defer s.mu.Unlock()
	s.groups[group.ID] = group
}

// CreateExpense is the single API entry point for adding an expense.
// It resolves user IDs, builds the expense with the correct split strategy,
// validates group membership, and updates balances — all in one call.
func (s *SplitwiseService) CreateExpense(groupID string, id string, amount float64, desc string, paidByID string, expType ExpenseType, participants []Participant) (*Expense, error) {
	s.mu.Lock()
	defer s.mu.Unlock()

	group, ok := s.groups[groupID]
	if !ok {
		return nil, fmt.Errorf("group %s not found", groupID)
	}

	paidBy, ok := s.users[paidByID]
	if !ok {
		return nil, fmt.Errorf("payer %s not found", paidByID)
	}

	// Pass an unlocked lookup since we already hold the lock
	lookup := func(userID string) (*User, bool) {
		u, ok := s.users[userID]
		return u, ok
	}

	expense, err := NewExpense(id, amount, desc, paidBy, expType, participants, lookup)
	if err != nil {
		return nil, err
	}

	if err = group.AddExpense(expense); err != nil {
		return nil, err
	}

	s.updateBalances(expense)
	return expense, nil
}

func (s *SplitwiseService) updateBalances(expense *Expense) {
	payer := expense.PaidBy
	for _, split := range expense.Splits {
		user := split.User
		amount := split.Amount
		if user.ID == payer.ID {
			continue
		}
		// payer is owed `amount` by user
		s.balances[payer.ID][user.ID] += amount
		s.balances[user.ID][payer.ID] -= amount
	}
}

func (s *SplitwiseService) GetBalance(userID1, userID2 string) float64 {
	s.mu.RLock()
	defer s.mu.RUnlock()
	if b, ok := s.balances[userID1]; ok {
		return b[userID2]
	}
	return 0
}

// GetUserBalances returns all non-zero balances for a user.
// Positive = others owe this user. Negative = this user owes others.
func (s *SplitwiseService) GetUserBalances(userID string) map[string]float64 {
	s.mu.RLock()
	defer s.mu.RUnlock()
	result := make(map[string]float64)
	if b, ok := s.balances[userID]; ok {
		for otherID, amt := range b {
			if amt != 0 {
				result[otherID] = amt
			}
		}
	}
	return result
}

func (s *SplitwiseService) SettleBalance(userID1, userID2 string) (*Transaction, error) {
	s.mu.Lock()
	defer s.mu.Unlock()

	user1, ok1 := s.users[userID1]
	user2, ok2 := s.users[userID2]
	if !ok1 || !ok2 {
		return nil, fmt.Errorf("user not found")
	}

	balance := s.balances[userID1][userID2]
	if balance == 0 {
		return nil, fmt.Errorf("no balance to settle between %s and %s", user1.Name, user2.Name)
	}

	s.txCounter++
	txID := fmt.Sprintf("txn_%d", s.txCounter)

	var tx *Transaction
	if balance < 0 {
		// user1 owes user2
		tx = NewTransaction(txID, user1, user2, -balance)
	} else {
		// user2 owes user1
		tx = NewTransaction(txID, user2, user1, balance)
	}

	s.balances[userID1][userID2] = 0
	s.balances[userID2][userID1] = 0
	s.transactions = append(s.transactions, tx)

	return tx, nil
}

func (s *SplitwiseService) GetTransactions() []*Transaction {
	s.mu.RLock()
	defer s.mu.RUnlock()
	result := make([]*Transaction, len(s.transactions))
	copy(result, s.transactions)
	return result
}

// PrintBalances prints all non-zero balances in a human-readable format
func (s *SplitwiseService) PrintBalances() {
	s.mu.RLock()
	defer s.mu.RUnlock()

	fmt.Println("=== Current Balances ===")
	printed := make(map[string]bool)
	for uid1, bmap := range s.balances {
		for uid2, amt := range bmap {
			key := uid1 + ":" + uid2
			reverseKey := uid2 + ":" + uid1
			if amt > 0 && !printed[key] && !printed[reverseKey] {
				fmt.Printf("  %s owes %s: $%.2f\n", s.users[uid2].Name, s.users[uid1].Name, amt)
				printed[key] = true
				printed[reverseKey] = true
			}
		}
	}
}
