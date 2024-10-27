package restaurantmanagementsystem

type PaymentMethod int

const (
	Cash PaymentMethod = iota
	CreditCard
	MobilePayment
)
