package restaurantmanagementsystem

type PaymentStatus int

const (
	PaymentPending PaymentStatus = iota
	PaymentCompleted
	PaymentFailed
)
