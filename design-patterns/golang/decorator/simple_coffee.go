package decorator

// SimpleCoffee represents a basic coffee without any additions
type SimpleCoffee struct{}

// NewSimpleCoffee creates a new SimpleCoffee instance
func NewSimpleCoffee() *SimpleCoffee {
	return &SimpleCoffee{}
}

// GetDescription returns the description of the coffee
func (c *SimpleCoffee) GetDescription() string {
	return "Simple Coffee"
}

// Cost returns the cost of the coffee
func (c *SimpleCoffee) Cost() float64 {
	return 1.0
}
