package state

import "fmt"

// HasMoneyState represents the state after money is inserted
type HasMoneyState struct{}

func (s *HasMoneyState) SelectItem(context *VendingMachine, item string) {
	fmt.Println("Transaction in progress. Please wait.")
}

func (s *HasMoneyState) InsertCoin(context *VendingMachine, amount float64) {
	fmt.Println("Already received money. Dispensing item...")
}

func (s *HasMoneyState) DispenseItem(context *VendingMachine) {
	item := context.GetSelectedItem()
	amt := context.GetInsertedAmount()
	fmt.Printf("Dispensing '%s' for $%.2f. Thank you!\n", item, amt)
	context.Reset()
}
