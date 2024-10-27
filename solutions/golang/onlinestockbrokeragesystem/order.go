package onlinestockbrokeragesystem

type Order interface {
	Execute() error
}

type BaseOrder struct {
	orderId  string
	account  *Account
	stock    *Stock
	quantity int
	price    float64
	status   OrderStatus
}

func (o *BaseOrder) SetStatus(status OrderStatus) {
	o.status = status
}
