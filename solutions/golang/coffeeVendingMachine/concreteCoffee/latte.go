package concreteCoffee

import (
	"github.com/ashishps1/awesome-low-level-design/solutions/golang/coffeeVendingMachine/enums"
)

type Latte struct {
}

func (l Latte) Cost() int {
	return 60
}

func (l Latte) Recipe() map[enums.Ingredient]int {
	return map[enums.Ingredient]int{
		enums.MILK:   50, //50 ml milk
		enums.SUGAR:  0,  // 0 cubes sugar
		enums.COFFEE: 50, // 50 g coffee
	}
}

func (l Latte) Name() string {
	return enums.LATTE.String()
}
