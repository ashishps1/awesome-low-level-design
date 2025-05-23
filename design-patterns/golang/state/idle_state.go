package state

import "fmt"

// IdleState represents the state when the machine is waiting for item selection
type IdleState struct{}

func (s *IdleState) SelectItem(context *VendingMachine, item string) {
	fmt.Printf("Item '%s' selected. Please insert coins.\n", item)
	context.SetSelectedItem(item)
	context.SetState(&ItemSelectedState{})
}

func (s *IdleState) InsertCoin(context *VendingMachine, amount float64) {
	fmt.Println("Please select an item first.")
}

func (s *IdleState) DispenseItem(context *VendingMachine) {
	fmt.Println("Please select an item and insert coins first.")
}
