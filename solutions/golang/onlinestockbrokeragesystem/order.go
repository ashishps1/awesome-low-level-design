package onlinestockbrokeragesystem

type Order interface {
	Execute() error
	GetStatus() OrderStatus
	SetStatus(status OrderStatus)
}

type BaseOrder struct {
	OrderID  string
	Account  *Account
	Stock    *Stock
	Quantity int
	Price    float64
	Status   OrderStatus
}

func (o *BaseOrder) GetStatus() OrderStatus {
	return o.Status
}

func (o *BaseOrder) SetStatus(status OrderStatus) {
	o.Status = status
}
