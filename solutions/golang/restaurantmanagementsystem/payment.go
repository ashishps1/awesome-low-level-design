package restaurantmanagementsystem

type Payment struct {
	ID     int
	Amount float64
	Method PaymentMethod
	Status PaymentStatus
}

func NewPayment(id int, amount float64, method PaymentMethod, status PaymentStatus) *Payment {
	return &Payment{
		ID:     id,
		Amount: amount,
		Method: method,
		Status: status,
	}
}
