package onlineshopping

type ShoppingCart struct {
	items map[string]OrderItem
}

func NewShoppingCart() *ShoppingCart {
	return &ShoppingCart{items: make(map[string]OrderItem)}
}

func (c *ShoppingCart) AddItem(product *Product, quantity int) {
	item := c.items[product.ID]
	item.Quantity += quantity
	c.items[product.ID] = OrderItem{Product: product, Quantity: item.Quantity}
}

func (c *ShoppingCart) RemoveItem(productId string) {
	delete(c.items, productId)
}

func (c *ShoppingCart) GetItems() []OrderItem {
	items := []OrderItem{}
	for _, item := range c.items {
		items = append(items, item)
	}
	return items
}

func (c *ShoppingCart) Clear() {
	c.items = make(map[string]OrderItem)
}
