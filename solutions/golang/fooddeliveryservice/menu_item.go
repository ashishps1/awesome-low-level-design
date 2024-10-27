package fooddeliveryservice

import "sync"

type MenuItem struct {
	ID          string
	Name        string
	Description string
	Price       float64
	available   bool
	mu          sync.RWMutex
}

func NewMenuItem(id, name, description string, price float64) *MenuItem {
	return &MenuItem{
		ID:          id,
		Name:        name,
		Description: description,
		Price:       price,
		available:   true,
	}
}

func (m *MenuItem) SetAvailable(available bool) {
	m.mu.Lock()
	defer m.mu.Unlock()
	m.available = available
}

func (m *MenuItem) IsAvailable() bool {
	m.mu.RLock()
	defer m.mu.RUnlock()
	return m.available
}
