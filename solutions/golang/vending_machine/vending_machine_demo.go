package vending_machine

import "fmt"

// Run demonstrates the Vending Machine functionality.
func Run() {
	// Initialize the vending machine
	vm := NewVendingMachine()

	// Create some products
	coke := NewProduct("Coke", 1.5)
	pepsi := NewProduct("Pepsi", 1.5)
	water := NewProduct("Water", 1.0)

	// Add products to the inventory
	vm.inventory.AddProduct(coke, 5)
	vm.inventory.AddProduct(pepsi, 3)
	vm.inventory.AddProduct(water, 2)

	// Demonstrate a transaction
	fmt.Println("Starting Vending Machine Demo")

	fmt.Println("\nSelecting Coke")
	vm.SelectProduct(coke)

	fmt.Println("Inserting coins")
	vm.InsertCoin(QUARTER)
	vm.InsertCoin(QUARTER)
	vm.InsertCoin(QUARTER)
	vm.InsertCoin(QUARTER)

	fmt.Println("Dispensing product")
	vm.DispenseProduct()

	fmt.Println("Returning change")
	vm.ReturnChange()

	// Another example with insufficient funds
	fmt.Println("\nSelecting Pepsi with insufficient funds")
	vm.SelectProduct(pepsi)
	vm.InsertCoin(QUARTER)

	fmt.Println("Trying to dispense Pepsi")
	vm.DispenseProduct()

	fmt.Println("Adding more coins for Pepsi")
	vm.InsertCoin(QUARTER)
	vm.InsertCoin(QUARTER)
	vm.InsertCoin(QUARTER)
	vm.InsertCoin(QUARTER)

	fmt.Println("Dispensing product")
	vm.DispenseProduct()

	fmt.Println("Returning change")
	vm.ReturnChange()
}
