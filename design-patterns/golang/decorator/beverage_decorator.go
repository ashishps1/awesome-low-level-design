package decorator

// BeverageDecorator is the base decorator that wraps a Beverage
type BeverageDecorator struct {
	beverage Beverage
}

// NewBeverageDecorator creates a new BeverageDecorator
func NewBeverageDecorator(beverage Beverage) *BeverageDecorator {
	return &BeverageDecorator{
		beverage: beverage,
	}
}

// GetDescription returns the description of the decorated beverage
func (d *BeverageDecorator) GetDescription() string {
	return d.beverage.GetDescription()
}

// Cost returns the cost of the decorated beverage
func (d *BeverageDecorator) Cost() float64 {
	return d.beverage.Cost()
}
