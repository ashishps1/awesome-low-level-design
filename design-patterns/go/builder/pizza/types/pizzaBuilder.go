package pizza

type PizzaBuilder interface {
	UseDough()
	UseSauce()
	AddToppings()
	GetPizza() Pizza
	New() *PizzaBuilder
}
