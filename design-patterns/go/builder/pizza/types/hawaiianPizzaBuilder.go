package pizza

type HawaiianPizzaBuilder struct {
	pizza *Pizza
}

/**
UseDough()
UseSauce()
AddToppings()
GetPizza() Pizza
New() *PizzaBuilder
*/

func (h *HawaiianPizzaBuilder) UseDough() {
}

func (h *HawaiianPizzaBuilder) UseSauce() {
}

func (h *HawaiianPizzaBuilder) AddToppings() {
	*h.pizza.Toppings = append(*h.pizza.Toppings, "olives")
}

func (h *HawaiianPizzaBuilder) GetPizza() Pizza {
	return *h.pizza
}

func (h *HawaiianPizzaBuilder) New() *HawaiianPizzaBuilder {
	return &HawaiianPizzaBuilder{
		pizza: NewPizza(),
	}
}
