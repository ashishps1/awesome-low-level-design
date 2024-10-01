package types

type Waiter struct {
	pizzaBuilder PizzaBuilder
}

func NewWaiter(pz PizzaBuilder) *Waiter {
	return &Waiter{
		pizzaBuilder: pz,
	}
}

func (w *Waiter) GetPizza() Pizza {
	return w.pizzaBuilder.GetPizza()
}

func (w *Waiter) SetPizzaBuilder(pb PizzaBuilder) {
	w.pizzaBuilder = pb
}

func (w *Waiter) CookPizza() {
	w.pizzaBuilder.UseDough()
	w.pizzaBuilder.UseSauce()
	w.pizzaBuilder.AddToppings()
}
