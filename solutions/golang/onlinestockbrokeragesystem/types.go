package onlinestockbrokeragesystem

type OrderStatus int

const (
	OrderStatusPending OrderStatus = iota
	OrderStatusExecuted
	OrderStatusRejected
)
