package machine

import (
	"fmt"
	"github.com/ashishps1/awesome-low-level-design/solutions/golang/coffeeVendingMachine/concreteCoffee"
	"github.com/ashishps1/awesome-low-level-design/solutions/golang/coffeeVendingMachine/enums"
	"github.com/ashishps1/awesome-low-level-design/solutions/golang/coffeeVendingMachine/interfaces"
	"sync"
)

var (
	instance *CoffeeMachine
	once     sync.Once
)

type CoffeeMachine struct {
	menu          map[interfaces.Coffee]bool
	inventory     Inventory
	currentCoffee interfaces.Coffee
	coffeeFactory *CoffeeFactory
}

func GetCoffeeMachineInstance() *CoffeeMachine {
	once.Do(func() {
		instance = &CoffeeMachine{
			menu: map[interfaces.Coffee]bool{
				concreteCoffee.Cappuccino{}: true,
				concreteCoffee.Latte{}:      true,
				concreteCoffee.Mocha{}:      true,
			},
			inventory: Inventory{map[enums.Ingredient]*quantity{
				enums.MILK: {
					current:   2000,
					threshold: 500,
				},
				enums.SUGAR: {
					current:   100,
					threshold: 15,
				},
				enums.COFFEE: {
					current:   500,
					threshold: 50,
				},
			}},
			coffeeFactory: &CoffeeFactory{},
		}
	})
	return instance
}

func (c *CoffeeMachine) DisplayMenu() {
	fmt.Println("Here are the available coffees")
	for coffee, available := range c.menu {
		if available {
			fmt.Printf("1) %s for Rs. %d", coffee.Name(), coffee.Cost())
		}
	}
}

func (c *CoffeeMachine) SelectCoffee(coffee enums.CoffeeType) {
	c.currentCoffee = c.coffeeFactory.GetCoffee(coffee)
}

func (c *CoffeeMachine) DispenseCoffee() {
	isAvailable := c.inventory.Check(c.currentCoffee.Recipe())
	if !isAvailable {
		fmt.Printf("%s is not available\n", c.currentCoffee.Name())
		return
	}
	// if available then refresh inventory
	fmt.Printf("Preparing %s\n", c.currentCoffee.Name())
	c.inventory.RefreshInventory(c.currentCoffee.Recipe())
}

func (c *CoffeeMachine) GetCurrentInventoryStatus() {
	for ingredient, quant := range c.inventory.TotalIngredients {
		fmt.Printf("Ingredient: %s, current value: %d, threshold: %d\n", ingredient.String(), quant.current, quant.threshold)
	}
}
