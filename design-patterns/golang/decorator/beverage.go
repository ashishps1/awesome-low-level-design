package decorator

// Beverage defines the interface for all beverages
type Beverage interface {
	GetDescription() string
	Cost() float64
}
