package fooddeliveryservice

type OrderStatus int

const (
	OrderStatusPending OrderStatus = iota
	OrderStatusConfirmed
	OrderStatusPreparing
	OrderStatusOutForDelivery
	OrderStatusDelivered
	OrderStatusCancelled
)

func (s OrderStatus) String() string {
	return [...]string{
		"PENDING",
		"CONFIRMED",
		"PREPARING",
		"OUT_FOR_DELIVERY",
		"DELIVERED",
		"CANCELLED",
	}[s]
}
