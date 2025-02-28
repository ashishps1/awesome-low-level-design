package vending_machine

import "fmt"

type VendingMachineState interface {
	SelectProduct(product *Product)
	InsertCoin(coin Coin)
	InsertNote(note Note)
	DispenseProduct()
	ReturnChange()
}

// IdleState struct
type IdleState struct {
	vendingMachine *VendingMachine
}

func (s *IdleState) SelectProduct(product *Product) {
	if s.vendingMachine.inventory.IsAvailable(product) {
		s.vendingMachine.selectedProduct = product
		s.vendingMachine.SetState(s.vendingMachine.readyState)
		fmt.Println("Product selected:", product.name)
	} else {
		fmt.Println("Product not available:", product.name)
	}
}

func (s *IdleState) InsertCoin(coin Coin) { fmt.Println("Please select a product first.") }
func (s *IdleState) InsertNote(note Note) { fmt.Println("Please select a product first.") }
func (s *IdleState) DispenseProduct()     { fmt.Println("Please select a product and make payment.") }
func (s *IdleState) ReturnChange()        { fmt.Println("No change to return.") }

// ReadyState struct
type ReadyState struct {
	vendingMachine *VendingMachine
}

func (s *ReadyState) SelectProduct(product *Product) {
	fmt.Println("Product already selected. Please make payment.")
}

func (s *ReadyState) InsertCoin(coin Coin) {
	s.vendingMachine.totalPayment += float64(coin)
	fmt.Println("Coin inserted:", coin)
	s.checkPaymentStatus()
}

func (s *ReadyState) InsertNote(note Note) {
	s.vendingMachine.totalPayment += float64(note)
	fmt.Println("Note inserted:", note)
	s.checkPaymentStatus()
}

func (s *ReadyState) DispenseProduct() { fmt.Println("Please make payment first.") }
func (s *ReadyState) ReturnChange() {
	change := s.vendingMachine.totalPayment - s.vendingMachine.selectedProduct.price
	if change > 0 {
		fmt.Printf("Change returned: $%.2f\n", change)
		s.vendingMachine.ResetPayment()
	} else {
		fmt.Println("No change to return.")
	}
	s.vendingMachine.SetState(s.vendingMachine.idleState)
}

func (s *ReadyState) checkPaymentStatus() {
	if s.vendingMachine.totalPayment >= s.vendingMachine.selectedProduct.price {
		s.vendingMachine.SetState(s.vendingMachine.dispenseState)
	}
}

// DispenseState struct
type DispenseState struct {
	vendingMachine *VendingMachine
}

func (s *DispenseState) SelectProduct(product *Product) { fmt.Println("Product already selected.") }
func (s *DispenseState) InsertCoin(coin Coin)           { fmt.Println("Please collect the product.") }
func (s *DispenseState) InsertNote(note Note)           { fmt.Println("Please collect the product.") }
func (s *DispenseState) DispenseProduct() {
	fmt.Println("Product dispensed:", s.vendingMachine.selectedProduct.name)
	s.vendingMachine.SetState(s.vendingMachine.returnChangeState)
}

func (s *DispenseState) ReturnChange() { fmt.Println("Please collect the product first.") }

// ReturnChangeState struct
type ReturnChangeState struct {
	vendingMachine *VendingMachine
}

func (s *ReturnChangeState) SelectProduct(product *Product) {
	fmt.Println("Please collect the change first.")
}
func (s *ReturnChangeState) InsertCoin(coin Coin) { fmt.Println("Please collect the change first.") }
func (s *ReturnChangeState) InsertNote(note Note) { fmt.Println("Please collect the change first.") }
func (s *ReturnChangeState) DispenseProduct() {
	fmt.Println("Product already dispensed. Please collect the change.")
}
func (s *ReturnChangeState) ReturnChange() {
	change := s.vendingMachine.totalPayment - s.vendingMachine.selectedProduct.price
	if change > 0 {
		fmt.Printf("Change returned: $%.2f\n", change)
		s.vendingMachine.ResetPayment()
	} else {
		fmt.Println("No change to return.")
	}
	s.vendingMachine.ResetSelectedProduct()
	s.vendingMachine.SetState(s.vendingMachine.idleState)
}
