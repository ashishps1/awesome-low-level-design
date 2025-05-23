package state

// MachineState defines the interface for vending machine states
type MachineState interface {
	SelectItem(context *VendingMachine, item string)
	InsertCoin(context *VendingMachine, amount float64)
	DispenseItem(context *VendingMachine)
}
