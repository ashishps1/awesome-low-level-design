package state

import "fmt"

// VendingMachine is the context that maintains the current state
type VendingMachine struct {
	state        MachineState
	selectedItem string
	insertedAmt  float64
}

func NewVendingMachine() *VendingMachine {
	return &VendingMachine{
		state: &IdleState{},
	}
}

func (vm *VendingMachine) SetState(state MachineState) {
	vm.state = state
}

func (vm *VendingMachine) SetSelectedItem(item string) {
	vm.selectedItem = item
}

func (vm *VendingMachine) SetInsertedAmount(amount float64) {
	vm.insertedAmt = amount
}

func (vm *VendingMachine) GetSelectedItem() string {
	return vm.selectedItem
}

func (vm *VendingMachine) GetInsertedAmount() float64 {
	return vm.insertedAmt
}

func (vm *VendingMachine) SelectItem(item string) {
	vm.state.SelectItem(vm, item)
}

func (vm *VendingMachine) InsertCoin(amount float64) {
	vm.state.InsertCoin(vm, amount)
}

func (vm *VendingMachine) DispenseItem() {
	vm.state.DispenseItem(vm)
}

func (vm *VendingMachine) Reset() {
	fmt.Println("Resetting vending machine...")
	vm.selectedItem = ""
	vm.insertedAmt = 0
	vm.state = &IdleState{}
}
