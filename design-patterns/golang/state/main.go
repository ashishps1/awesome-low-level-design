package state

func main() {
	vm := NewVendingMachine()

	// Try to insert coin before selecting item
	vm.InsertCoin(1.0)

	// Select an item
	vm.SelectItem("Soda")

	// Insert coin
	vm.InsertCoin(1.5)

	// Dispense item
	vm.DispenseItem()

	// Try another transaction
	vm.SelectItem("Chips")
	vm.InsertCoin(2.0)
	vm.DispenseItem()
}
