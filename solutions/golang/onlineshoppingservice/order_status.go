package onlineshopping

type OrderStatus int

const (
	Pending OrderStatus = iota
	Processing
	Shipped
	Delivered
	Cancelled
)
