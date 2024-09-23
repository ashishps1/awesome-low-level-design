package pizza

import "fmt"

type Pizza struct {
	Dough    string
	Sauce    string
	Toppings []string
}

func NewPizza() *Pizza {
	return &Pizza{
		Toppings: make([]string, 0),
	}
}

func (p Pizza) Description() string {
	s := "Pizza has %s dough, %s sauce, %s topping\n"
	return fmt.Sprintf(s, p.Dough, p.Sauce, p.Toppings)
}
