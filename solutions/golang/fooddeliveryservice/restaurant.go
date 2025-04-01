package fooddeliveryservice

import "sync"

type Restaurant struct {
	ID      string
	Name    string
	Address string
	Menu    []*MenuItem
	mu      sync.RWMutex
}

func NewRestaurant(id, name, address string, menu []*MenuItem) *Restaurant {
	return &Restaurant{
		ID:      id,
		Name:    name,
		Address: address,
		Menu:    menu,
	}
}

func (r *Restaurant) AddMenuItem(item *MenuItem) {
	r.mu.Lock()
	defer r.mu.Unlock()
	r.Menu = append(r.Menu, item)
}

func (r *Restaurant) RemoveMenuItem(item *MenuItem) {
	r.mu.Lock()
	defer r.mu.Unlock()
	for i, menuItem := range r.Menu {
		if menuItem == item {
			r.Menu = append(r.Menu[:i], r.Menu[i+1:]...)
			break
		}
	}
}

func (r *Restaurant) GetMenu() []*MenuItem {
	r.mu.RLock()
	defer r.mu.RUnlock()
	menuCopy := make([]*MenuItem, len(r.Menu))
	copy(menuCopy, r.Menu)
	return menuCopy
}
