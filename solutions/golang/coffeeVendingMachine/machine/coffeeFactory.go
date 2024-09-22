package machine

import (
	"github.com/ashishps1/awesome-low-level-design/solutions/golang/coffeeVendingMachine/concreteCoffee"
	"github.com/ashishps1/awesome-low-level-design/solutions/golang/coffeeVendingMachine/enums"
	"github.com/ashishps1/awesome-low-level-design/solutions/golang/coffeeVendingMachine/interfaces"
)

type CoffeeFactory struct {
}

func (c *CoffeeFactory) GetCoffee(coffee enums.CoffeeType) interfaces.Coffee {
	switch coffee {
	case enums.CAPPUCCINO:
		return &concreteCoffee.Cappuccino{}
	case enums.MOCHA:
		return &concreteCoffee.Mocha{}
	case enums.LATTE:
		return &concreteCoffee.Latte{}
	}
	return nil
}
