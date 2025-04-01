package coffeevendingmachine

type Coffee struct {
	name   string
	price  float64
	recipe map[*Ingredient]int
}

func NewCoffee(name string, price float64, recipe map[*Ingredient]int) *Coffee {
	return &Coffee{
		name:   name,
		price:  price,
		recipe: recipe,
	}
}

func (c *Coffee) GetName() string {
	return c.name
}

func (c *Coffee) GetPrice() float64 {
	return c.price
}

func (c *Coffee) GetRecipe() map[*Ingredient]int {
	return c.recipe
}
