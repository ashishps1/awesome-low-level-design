package types

type SpicyPizzaBuilder struct {
	pizza *Pizza
}

func NewSpicyPizzaBuilder() PizzaBuilder {
	return &SpicyPizzaBuilder{
		pizza: NewPizza(),
	}
}

func (s *SpicyPizzaBuilder) UseDough() {
	s.pizza.Dough = "Thick CheeseNaan Crust"
}

func (s *SpicyPizzaBuilder) UseSauce() {
	s.pizza.Sauce = "Desi Masala Hari and Lal Mirchi Sauce"
}

func (s *SpicyPizzaBuilder) AddToppings() {
	s.pizza.Toppings = append(s.pizza.Toppings, "paneer", "onions", "chilli", "corn", "tomato")
}

func (s *SpicyPizzaBuilder) GetPizza() Pizza {
	return *s.pizza
}

func (s *SpicyPizzaBuilder) New() PizzaBuilder {
	return &SpicyPizzaBuilder{
		pizza: NewPizza(),
	}
}
