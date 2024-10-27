package restaurantmanagementsystem

type MenuItem struct {
	ID          int
	Name        string
	Description string
	Price       float64
	Available   bool
}

func NewMenuItem(id int, name, description string, price float64, available bool) *MenuItem {
	return &MenuItem{
		ID:          id,
		Name:        name,
		Description: description,
		Price:       price,
		Available:   available,
	}
}
