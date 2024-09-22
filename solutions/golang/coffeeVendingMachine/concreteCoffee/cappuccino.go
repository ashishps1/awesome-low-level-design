package concreteCoffee

import (
	"github.com/ashishps1/awesome-low-level-design/solutions/golang/coffeeVendingMachine/enums"
)

type Cappuccino struct {
}

func (c Cappuccino) Cost() int {
	return 20
}

func (c Cappuccino) Recipe() map[enums.Ingredient]int {
	return map[enums.Ingredient]int{
		enums.MILK:   200, //200 ml milk
		enums.SUGAR:  2,   // 2 cubes sugar
		enums.COFFEE: 30,  // 30 g coffee
	}
}

func (c Cappuccino) Name() string {
	return enums.CAPPUCCINO.String()
}
