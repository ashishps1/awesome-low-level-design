package splitwise

import "fmt"

func Run() {
	ResetService()
	service := GetService()

	// --- Create Users ---
	alice := NewUser("1", "Alice", "alice@example.com")
	bob := NewUser("2", "Bob", "bob@example.com")
	charlie := NewUser("3", "Charlie", "charlie@example.com")
	diana := NewUser("4", "Diana", "diana@example.com")

	service.AddUser(alice)
	service.AddUser(bob)
	service.AddUser(charlie)
	service.AddUser(diana)

	// --- Create Group ---
	group := NewGroup("g1", "Apartment")
	group.AddMember(alice)
	group.AddMember(bob)
	group.AddMember(charlie)
	group.AddMember(diana)
	service.AddGroup(group)

	// --- Expense 1: Equal Split ---
	// For equal, Value is ignored — just list the user IDs
	fmt.Println(">>> Expense 1: Alice pays $300 rent (equal split)")
	_, err := service.CreateExpense("g1", "e1", 300, "Rent", "1", Equal, []Participant{
		{UserID: "1"}, {UserID: "2"}, {UserID: "3"},
	})
	if err != nil {
		fmt.Println("Error:", err)
		return
	}
	service.PrintBalances()

	// --- Expense 2: Percent Split ---
	// Value = percentage share
	fmt.Println("\n>>> Expense 2: Bob pays $200 groceries (percent split)")
	_, err = service.CreateExpense("g1", "e2", 200, "Groceries", "2", Percent, []Participant{
		{UserID: "1", Value: 25},
		{UserID: "2", Value: 25},
		{UserID: "3", Value: 25},
		{UserID: "4", Value: 25},
	})
	if err != nil {
		fmt.Println("Error:", err)
		return
	}
	service.PrintBalances()

	// --- Expense 3: Exact Split ---
	// Value = exact dollar amount
	fmt.Println("\n>>> Expense 3: Charlie pays $150 dinner (exact split)")
	_, err = service.CreateExpense("g1", "e3", 150, "Dinner", "3", Exact, []Participant{
		{UserID: "1", Value: 50},
		{UserID: "2", Value: 30},
		{UserID: "3", Value: 40},
		{UserID: "4", Value: 30},
	})
	if err != nil {
		fmt.Println("Error:", err)
		return
	}
	service.PrintBalances()

	// --- Settle ---
	fmt.Println("\n>>> Settling Bob's debt with Alice")
	tx, err := service.SettleBalance("2", "1")
	if err != nil {
		fmt.Println("Error:", err)
	} else {
		fmt.Println("  ", tx)
	}

	fmt.Println("\n>>> Final Balances")
	service.PrintBalances()

	fmt.Println("\n>>> Transaction History")
	for _, t := range service.GetTransactions() {
		fmt.Println("  ", t)
	}

	// --- Validation: bad percent ---
	fmt.Println("\n>>> Validation: percent that doesn't sum to 100")
	_, err = service.CreateExpense("g1", "e4", 100, "Bad", "1", Percent, []Participant{
		{UserID: "1", Value: 50},
		{UserID: "2", Value: 30},
	})
	fmt.Println("  Error:", err)

	// --- Validation: unknown user ---
	fmt.Println("\n>>> Validation: unknown user ID")
	_, err = service.CreateExpense("g1", "e5", 100, "Bad", "1", Equal, []Participant{
		{UserID: "1"}, {UserID: "999"},
	})
	fmt.Println("  Error:", err)
}
