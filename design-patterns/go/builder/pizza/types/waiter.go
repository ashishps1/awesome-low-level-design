package pizza

type Waiter struct {
	pizzaBuilder *PizzaBuilder
}

func (w Waiter) GetPizza() Pizza {
	return (*w.pizzaBuilder).GetPizza()
}

func (w Waiter) SetPizzaBuilder(pb *PizzaBuilder) {
	w.pizzaBuilder = pb
}

func (w Waiter) CookPizza(pb *PizzaBuilder) {
	(*w.pizzaBuilder).UseDough()
	(*w.pizzaBuilder).UseSauce()
	(*w.pizzaBuilder).AddToppings()
}
