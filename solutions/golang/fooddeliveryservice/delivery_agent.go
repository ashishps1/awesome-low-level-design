package fooddeliveryservice

import "sync"

type DeliveryAgent struct {
	ID        string
	Name      string
	Phone     string
	available bool
	mu        sync.RWMutex
}

func NewDeliveryAgent(id, name, phone string) *DeliveryAgent {
	return &DeliveryAgent{
		ID:        id,
		Name:      name,
		Phone:     phone,
		available: true,
	}
}

func (d *DeliveryAgent) SetAvailable(available bool) {
	d.mu.Lock()
	defer d.mu.Unlock()
	d.available = available
}

func (d *DeliveryAgent) IsAvailable() bool {
	d.mu.RLock()
	defer d.mu.RUnlock()
	return d.available
}
