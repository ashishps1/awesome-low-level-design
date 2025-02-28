package onlineshopping

type OrderItem struct {
	Product  *Product
	Quantity int
}

func NewOrderItem(product *Product, quantity int) OrderItem {
	return OrderItem{Product: product, Quantity: quantity}
}
