package splitwise

import (
	"fmt"
)

func Run() {
	service := GetSplitwiseService()

	// Create users
	user1 := NewUser("1", "Alice", "alice@example.com")
	user2 := NewUser("2", "Bob", "bob@example.com")
	user3 := NewUser("3", "Charlie", "charlie@example.com")
	service.AddUser(user1)
	service.AddUser(user2)
	service.AddUser(user3)

	// Create group and add users
	group := NewGroup("1", "Apartment")
	group.AddMember(user1)
	group.AddMember(user2)
	group.AddMember(user3)
	service.AddGroup(group)

	// Add expense
	expense := NewExpense("1", 300, "Rent", user1)
	expense.AddSplit(NewEqualSplit(user1))
	expense.AddSplit(NewEqualSplit(user2))
	expense.AddSplit(NewPercentSplit(user3, 20))
	service.AddExpense(group.ID, expense)

	// Settle balances
	service.SettleBalance(user1.ID, user2.ID)
	service.SettleBalance(user1.ID, user3.ID)

	// Print balances
	for _, user := range []*User{user1, user2, user3} {
		fmt.Printf("User: %s\n", user.Name)
		for key, balance := range user.Balances {
			fmt.Printf("  Balance with %s: %.2f\n", key, balance)
		}
	}
}
