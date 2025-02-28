package types

type HawaiianPizzaBuilder struct {
	pizza *Pizza
}

func NewHawaiianPizzaBuilder() PizzaBuilder {
	return &HawaiianPizzaBuilder{
		pizza: NewPizza(),
	}
}

func (h *HawaiianPizzaBuilder) UseDough() {
	h.pizza.Dough = "Buttery Crunchy Thin Crust"
}

func (h *HawaiianPizzaBuilder) UseSauce() {
	h.pizza.Sauce = "Hawaiian Chilli Sauce"
}

func (h *HawaiianPizzaBuilder) AddToppings() {
	h.pizza.Toppings = append(h.pizza.Toppings, "olives", "capsicum", "feta", "tomato")
}

func (h *HawaiianPizzaBuilder) GetPizza() Pizza {
	return *h.pizza
}

func (h *HawaiianPizzaBuilder) New() PizzaBuilder {
	return &HawaiianPizzaBuilder{
		pizza: NewPizza(),
	}
}
