package coffeevendingmachine

import (
	"fmt"
)

func Run() {
	coffeeMachine := GetCoffeeMachine()

	// Display coffee menu
	coffeeMachine.DisplayMenu()

	// Simulate user requests
	coffeeTypes := []string{"Espresso", "Cappuccino", "Latte"}
	payments := []float64{3.0, 3.5, 4.0}

	for i, coffeeType := range coffeeTypes {
		selectedCoffee := coffeeMachine.SelectCoffee(coffeeType)
		payment := NewPayment(payments[i])

		fmt.Printf("\nOrdering %s...\n", coffeeType)
		if err := coffeeMachine.DispenseCoffee(selectedCoffee, payment); err != nil {
			fmt.Printf("Error: %v\n", err)
		}
	}
}
