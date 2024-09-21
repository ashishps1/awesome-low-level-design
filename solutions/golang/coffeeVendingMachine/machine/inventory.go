package machine

import (
	"fmt"
	"github.com/ashishps1/awesome-low-level-design/coffeeVendingMachine/enums"
)

type quantity struct {
	current   int
	threshold int
}
type Inventory struct {
	TotalIngredients map[enums.Ingredient]*quantity
}

func NewInventory() *Inventory {
	return &Inventory{
		TotalIngredients: make(map[enums.Ingredient]*quantity),
	}
}

func (i *Inventory) Add(ingredient enums.Ingredient, amount int, threshold int) {
	i.TotalIngredients[ingredient] = &quantity{
		current:   amount,
		threshold: threshold,
	}
}

func (i *Inventory) Check(ingredients map[enums.Ingredient]int) bool {
	for ingredient, amount := range ingredients {
		if i.TotalIngredients[ingredient].current < amount {
			return false
		}
	}
	return true
}

func (i *Inventory) RefreshInventory(ingredients map[enums.Ingredient]int) {
	for ingredient, amount := range ingredients {
		i.TotalIngredients[ingredient].current -= amount
		if i.TotalIngredients[ingredient].current < i.TotalIngredients[ingredient].threshold {
			fmt.Printf("%s needs refill, running low!\n", ingredient.String())
		}
	}
}
