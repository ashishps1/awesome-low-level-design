package restaurantmanagementsystem

import (
	"time"
)

type Order struct {
	ID          int
	Items       []MenuItem
	TotalAmount float64
	Status      OrderStatus
	Timestamp   time.Time
}

func NewOrder(id int, items []MenuItem, totalAmount float64, status OrderStatus) *Order {
	return &Order{
		ID:          id,
		Items:       items,
		TotalAmount: totalAmount,
		Status:      status,
		Timestamp:   time.Now(),
	}
}

func (o *Order) SetStatus(status OrderStatus) {
	o.Status = status
}
