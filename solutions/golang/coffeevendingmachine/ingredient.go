package coffeevendingmachine

import "sync"

type Ingredient struct {
	name     string
	quantity int
	mu       sync.Mutex
}

func NewIngredient(name string, quantity int) *Ingredient {
	return &Ingredient{
		name:     name,
		quantity: quantity,
	}
}

func (i *Ingredient) GetName() string {
	return i.name
}

func (i *Ingredient) GetQuantity() int {
	i.mu.Lock()
	defer i.mu.Unlock()
	return i.quantity
}

func (i *Ingredient) UpdateQuantity(amount int) {
	i.mu.Lock()
	defer i.mu.Unlock()
	i.quantity += amount
}
