package decorator

// MilkDecorator adds milk to a beverage
type MilkDecorator struct {
	*BeverageDecorator
}

// NewMilkDecorator creates a new MilkDecorator
func NewMilkDecorator(beverage Beverage) *MilkDecorator {
	return &MilkDecorator{
		BeverageDecorator: NewBeverageDecorator(beverage),
	}
}

// GetDescription returns the description of the beverage with milk
func (d *MilkDecorator) GetDescription() string {
	return d.beverage.GetDescription() + " with Milk"
}

// Cost returns the cost of the beverage with milk
func (d *MilkDecorator) Cost() float64 {
	return d.beverage.Cost() + 0.5
}
