package vending_machine

type Inventory struct {
	products map[*Product]int
}

func NewInventory() *Inventory {
	return &Inventory{products: make(map[*Product]int)}
}

func (inv *Inventory) AddProduct(product *Product, quantity int) {
	inv.products[product] = quantity
}

func (inv *Inventory) IsAvailable(product *Product) bool {
	qty, exists := inv.products[product]
	return exists && qty > 0
}
