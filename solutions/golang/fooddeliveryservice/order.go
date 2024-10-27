package fooddeliveryservice

import "sync"

type OrderItem struct {
	MenuItem *MenuItem
	Quantity int
}

func NewOrderItem(menuItem *MenuItem, quantity int) *OrderItem {
	return &OrderItem{
		MenuItem: menuItem,
		Quantity: quantity,
	}
}

type Order struct {
	ID            string
	Customer      *Customer
	Restaurant    *Restaurant
	Items         []*OrderItem
	Status        OrderStatus
	DeliveryAgent *DeliveryAgent
	mu            sync.RWMutex
}

func NewOrder(id string, customer *Customer, restaurant *Restaurant) *Order {
	return &Order{
		ID:         id,
		Customer:   customer,
		Restaurant: restaurant,
		Items:      make([]*OrderItem, 0),
		Status:     OrderStatusPending,
	}
}

func (o *Order) AddItem(item *OrderItem) {
	o.mu.Lock()
	defer o.mu.Unlock()
	o.Items = append(o.Items, item)
}

func (o *Order) RemoveItem(item *OrderItem) {
	o.mu.Lock()
	defer o.mu.Unlock()
	for i, orderItem := range o.Items {
		if orderItem == item {
			o.Items = append(o.Items[:i], o.Items[i+1:]...)
			break
		}
	}
}

func (o *Order) SetStatus(status OrderStatus) {
	o.mu.Lock()
	defer o.mu.Unlock()
	o.Status = status
}

func (o *Order) GetStatus() OrderStatus {
	o.mu.RLock()
	defer o.mu.RUnlock()
	return o.Status
}

func (o *Order) AssignDeliveryAgent(agent *DeliveryAgent) {
	o.mu.Lock()
	defer o.mu.Unlock()
	o.DeliveryAgent = agent
}
