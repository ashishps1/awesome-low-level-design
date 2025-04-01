package splitwise

import (
	"fmt"
	"sync"
)

type SplitwiseService struct {
	users   map[string]*User
	groups  map[string]*Group
	counter int
	mu      sync.Mutex
}

var instance *SplitwiseService
var once sync.Once

func GetSplitwiseService() *SplitwiseService {
	once.Do(func() {
		instance = &SplitwiseService{
			users:  make(map[string]*User),
			groups: make(map[string]*Group),
		}
	})
	return instance
}

func (s *SplitwiseService) AddUser(user *User) {
	s.users[user.ID] = user
}

func (s *SplitwiseService) AddGroup(group *Group) {
	s.groups[group.ID] = group
}

func (s *SplitwiseService) AddExpense(groupID string, expense *Expense) {
	group, exists := s.groups[groupID]
	if !exists {
		return
	}
	group.AddExpense(expense)
	s.splitExpense(expense)
	s.updateBalances(expense)
}

func (s *SplitwiseService) splitExpense(expense *Expense) {
	totalAmount := expense.Amount
	totalSplits := len(expense.Splits)

	for _, split := range expense.Splits {
		switch v := split.(type) {
		case *EqualSplit:
			v.SetAmount(totalAmount / float64(totalSplits))
		case *PercentSplit:
			v.SetAmount(totalAmount * v.Percent / 100.0)
		}
	}
}

func (s *SplitwiseService) updateBalances(expense *Expense) {
	for _, split := range expense.Splits {
		paidBy := expense.PaidBy
		user := split.GetUser()
		amount := split.GetAmount()
		if paidBy != user {
			s.updateBalance(paidBy, user, amount)
			s.updateBalance(user, paidBy, -amount)
		}
	}
}

func (s *SplitwiseService) updateBalance(user1, user2 *User, amount float64) {
	key := user1.ID + ":" + user2.ID
	user1.Balances[key] += amount
}

func (s *SplitwiseService) SettleBalance(userID1, userID2 string) {
	user1, exists1 := s.users[userID1]
	user2, exists2 := s.users[userID2]
	if !exists1 || !exists2 {
		return
	}

	key := user1.ID + ":" + user2.ID
	balance := user1.Balances[key]

	if balance > 0 {
		s.createTransaction(user1, user2, balance)
		user1.Balances[key] = 0
		user2.Balances[user2.ID+":"+user1.ID] = 0
	} else if balance < 0 {
		s.createTransaction(user2, user1, -balance)
		user1.Balances[key] = 0
		user2.Balances[user2.ID+":"+user1.ID] = 0
	}
}

func (s *SplitwiseService) createTransaction(sender, receiver *User, amount float64) {
	fmt.Printf("Transaction: %s pays %s an amount of %.2f\n", sender.Name, receiver.Name, amount)
}
