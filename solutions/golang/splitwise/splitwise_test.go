package splitwise

import (
	"fmt"
	"math"
	"sync"
	"testing"
)

func setup() (*SplitwiseService, *User, *User, *User, *Group) {
	ResetService()
	svc := GetService()

	alice := NewUser("1", "Alice", "alice@example.com")
	bob := NewUser("2", "Bob", "bob@example.com")
	charlie := NewUser("3", "Charlie", "charlie@example.com")

	svc.AddUser(alice)
	svc.AddUser(bob)
	svc.AddUser(charlie)

	group := NewGroup("g1", "Test Group")
	group.AddMember(alice)
	group.AddMember(bob)
	group.AddMember(charlie)
	svc.AddGroup(group)

	return svc, alice, bob, charlie, group
}

func almostEqual(a, b float64) bool {
	return math.Abs(a-b) < 0.01
}

func TestEqualSplit(t *testing.T) {
	svc, _, _, _, _ := setup()

	_, err := svc.CreateExpense("g1", "e1", 300, "Rent", "1", Equal, []Participant{
		{UserID: "1"}, {UserID: "2"}, {UserID: "3"},
	})
	if err != nil {
		t.Fatal(err)
	}

	if !almostEqual(svc.GetBalance("1", "2"), 100) {
		t.Errorf("Alice->Bob balance: got %.2f, want 100", svc.GetBalance("1", "2"))
	}
	if !almostEqual(svc.GetBalance("1", "3"), 100) {
		t.Errorf("Alice->Charlie balance: got %.2f, want 100", svc.GetBalance("1", "3"))
	}
}

func TestPercentSplit(t *testing.T) {
	svc, _, _, _, _ := setup()

	_, err := svc.CreateExpense("g1", "e1", 200, "Groceries", "2", Percent, []Participant{
		{UserID: "1", Value: 50},
		{UserID: "2", Value: 30},
		{UserID: "3", Value: 20},
	})
	if err != nil {
		t.Fatal(err)
	}

	if !almostEqual(svc.GetBalance("2", "1"), 100) {
		t.Errorf("Bob->Alice balance: got %.2f, want 100", svc.GetBalance("2", "1"))
	}
	if !almostEqual(svc.GetBalance("2", "3"), 40) {
		t.Errorf("Bob->Charlie balance: got %.2f, want 40", svc.GetBalance("2", "3"))
	}
}

func TestExactSplit(t *testing.T) {
	svc, _, _, _, _ := setup()

	_, err := svc.CreateExpense("g1", "e1", 150, "Dinner", "1", Exact, []Participant{
		{UserID: "1", Value: 50},
		{UserID: "2", Value: 60},
		{UserID: "3", Value: 40},
	})
	if err != nil {
		t.Fatal(err)
	}

	if !almostEqual(svc.GetBalance("1", "2"), 60) {
		t.Errorf("Alice->Bob balance: got %.2f, want 60", svc.GetBalance("1", "2"))
	}
	if !almostEqual(svc.GetBalance("1", "3"), 40) {
		t.Errorf("Alice->Charlie balance: got %.2f, want 40", svc.GetBalance("1", "3"))
	}
}

func TestSettleBalance(t *testing.T) {
	svc, _, _, _, _ := setup()

	svc.CreateExpense("g1", "e1", 200, "Test", "1", Equal, []Participant{
		{UserID: "1"}, {UserID: "2"},
	})

	tx, err := svc.SettleBalance("2", "1")
	if err != nil {
		t.Fatal(err)
	}
	if tx.From.ID != "2" || tx.To.ID != "1" || !almostEqual(tx.Amount, 100) {
		t.Errorf("unexpected transaction: %s", tx)
	}
	if !almostEqual(svc.GetBalance("1", "2"), 0) {
		t.Errorf("balance not settled: %.2f", svc.GetBalance("1", "2"))
	}
}

func TestValidation_PercentMustSum100(t *testing.T) {
	svc, _, _, _, _ := setup()
	_, err := svc.CreateExpense("g1", "e1", 100, "Bad", "1", Percent, []Participant{
		{UserID: "1", Value: 50},
		{UserID: "2", Value: 30},
	})
	if err == nil {
		t.Error("expected error for percent shares not summing to 100")
	}
}

func TestValidation_ExactMustSumToAmount(t *testing.T) {
	svc, _, _, _, _ := setup()
	_, err := svc.CreateExpense("g1", "e1", 100, "Bad", "1", Exact, []Participant{
		{UserID: "1", Value: 50},
		{UserID: "2", Value: 30},
	})
	if err == nil {
		t.Error("expected error for exact shares not summing to amount")
	}
}

func TestValidation_NonMemberExpense(t *testing.T) {
	svc, _, _, _, _ := setup()
	svc.AddUser(NewUser("99", "Outsider", "out@example.com"))

	_, err := svc.CreateExpense("g1", "e1", 100, "Test", "1", Equal, []Participant{
		{UserID: "1"}, {UserID: "99"},
	})
	if err == nil {
		t.Error("expected error for non-member in expense")
	}
}

func TestValidation_UnknownUser(t *testing.T) {
	svc, _, _, _, _ := setup()
	_, err := svc.CreateExpense("g1", "e1", 100, "Test", "1", Equal, []Participant{
		{UserID: "1"}, {UserID: "999"},
	})
	if err == nil {
		t.Error("expected error for unknown user ID")
	}
}

func TestConcurrentExpenses(t *testing.T) {
	svc, _, _, _, _ := setup()

	var wg sync.WaitGroup
	for i := 0; i < 100; i++ {
		wg.Add(1)
		go func(i int) {
			defer wg.Done()
			svc.CreateExpense("g1", fmt.Sprintf("e%d", i), 90, "Concurrent", "1", Equal, []Participant{
				{UserID: "1"}, {UserID: "2"}, {UserID: "3"},
			})
		}(i)
	}
	wg.Wait()

	bobOwes := svc.GetBalance("1", "2")
	charlieOwes := svc.GetBalance("1", "3")
	if !almostEqual(bobOwes, 3000) {
		t.Errorf("concurrent Bob balance: got %.2f, want 3000", bobOwes)
	}
	if !almostEqual(charlieOwes, 3000) {
		t.Errorf("concurrent Charlie balance: got %.2f, want 3000", charlieOwes)
	}
}
