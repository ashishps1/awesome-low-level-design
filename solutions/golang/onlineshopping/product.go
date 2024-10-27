package onlineshopping

type Product struct {
	ID          string
	Name        string
	Description string
	Price       float64
	Quantity    int
}

func NewProduct(id, name, description string, price float64, quantity int) *Product {
	return &Product{
		ID:          id,
		Name:        name,
		Description: description,
		Price:       price,
		Quantity:    quantity,
	}
}

func (p *Product) UpdateQuantity(quantity int) {
	p.Quantity += quantity
}

func (p *Product) IsAvailable(quantity int) bool {
	return p.Quantity >= quantity
}
