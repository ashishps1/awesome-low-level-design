package onlineshopping

type Order struct {
	ID          string
	User        *User
	Items       []OrderItem
	TotalAmount float64
	Status      OrderStatus
}

func NewOrder(id string, user *User, items []OrderItem) *Order {
	order := &Order{
		ID:     id,
		User:   user,
		Items:  items,
		Status: Pending,
	}
	order.TotalAmount = order.calculateTotalAmount()
	return order
}

func (o *Order) calculateTotalAmount() float64 {
	total := 0.0
	for _, item := range o.Items {
		total += item.Product.Price * float64(item.Quantity)
	}
	return total
}

func (o *Order) SetStatus(status OrderStatus) {
	o.Status = status
}
