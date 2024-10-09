package main

import (
	"github.com/ashishps1/awesome-low-level-design/solutions/golang/coffeeVendingMachine/enums"
	"github.com/ashishps1/awesome-low-level-design/solutions/golang/coffeeVendingMachine/machine"
)

func main() {
	coffeeMachine := machine.GetCoffeeMachineInstance()

	coffeeMachine.GetCurrentInventoryStatus()

	coffeeMachine.SelectCoffee(enums.CAPPUCCINO)
	coffeeMachine.DispenseCoffee()

	coffeeMachine.GetCurrentInventoryStatus()

	coffeeMachine.SelectCoffee(enums.LATTE)
	coffeeMachine.DispenseCoffee()

	coffeeMachine.GetCurrentInventoryStatus()
}
