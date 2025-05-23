package state

import "fmt"

// ItemSelectedState represents the state after an item is selected
type ItemSelectedState struct{}

func (s *ItemSelectedState) SelectItem(context *VendingMachine, item string) {
	fmt.Println("Item already selected. Please insert coins.")
}

func (s *ItemSelectedState) InsertCoin(context *VendingMachine, amount float64) {
	fmt.Printf("Inserted $%.2f.\n", amount)
	context.SetInsertedAmount(amount)
	context.SetState(&HasMoneyState{})
}

func (s *ItemSelectedState) DispenseItem(context *VendingMachine) {
	fmt.Println("Please insert coins before dispensing the item.")
}
