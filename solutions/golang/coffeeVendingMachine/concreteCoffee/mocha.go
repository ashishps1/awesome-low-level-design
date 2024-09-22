package concreteCoffee

import (
	"github.com/ashishps1/awesome-low-level-design/solutions/golang/coffeeVendingMachine/enums"
)

type Mocha struct {
}

func (m Mocha) Cost() int {
	return 40
}

func (m Mocha) Recipe() map[enums.Ingredient]int {
	return map[enums.Ingredient]int{
		enums.MILK:   100, //100 ml milk
		enums.SUGAR:  1,   // 1 cubes sugar
		enums.COFFEE: 40,  // 40 g coffee
	}
}

func (m Mocha) Name() string {
	return enums.MOCHA.String()
}
