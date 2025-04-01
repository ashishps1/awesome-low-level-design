package restaurantmanagementsystem

type OrderStatus int

const (
	OrderPending OrderStatus = iota
	OrderPreparing
	OrderReady
	OrderCompleted
	OrderCancelled
)
