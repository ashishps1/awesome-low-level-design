package enums

type CoffeeType int

const (
	CAPPUCCINO CoffeeType = iota + 1
	MOCHA
	LATTE
)

func (ct CoffeeType) String() string {
	return [...]string{"CAPPUCCINO", "MOCHA", "LATTE"}[ct-1]
}
