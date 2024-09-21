package interfaces

import "github.com/ashishps1/awesome-low-level-design/coffeeVendingMachine/enums"

type Coffee interface {
	Cost() int
	Recipe() map[enums.Ingredient]int
	Name() string
}
