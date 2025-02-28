package main

import (
	"fmt"
	"github.com/VishalMCF/awesome-low-level-design/design-patterns/builder/pizza/types"
)

func main() {
	fmt.Println("This is the demo for Pizza Builder")

	// Initialize builders using constructor functions
	hpb := types.NewHawaiianPizzaBuilder()
	spb := types.NewSpicyPizzaBuilder()

	// Create waiters with the respective builders
	w1 := types.NewWaiter(hpb)
	w2 := types.NewWaiter(spb)

	// Cook and get the Hawaiian Pizza
	w1.CookPizza()
	pizza1 := w1.GetPizza()
	fmt.Println(pizza1.Description())

	// Cook and get the Spicy Pizza
	w2.CookPizza()
	pizza2 := w2.GetPizza()
	fmt.Println(pizza2.Description())
}
