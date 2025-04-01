package restaurantmanagementsystem

import "sync"

type Restaurant struct {
	menu         []MenuItem
	orders       map[int]*Order
	reservations []Reservation
	payments     map[int]*Payment
	staff        []Staff
	mu           sync.Mutex
}

var restaurantInstance *Restaurant
var once sync.Once

func GetRestaurantInstance() *Restaurant {
	once.Do(func() {
		restaurantInstance = &Restaurant{
			menu:         []MenuItem{},
			orders:       make(map[int]*Order),
			reservations: []Reservation{},
			payments:     make(map[int]*Payment),
			staff:        []Staff{},
		}
	})
	return restaurantInstance
}

func (r *Restaurant) AddMenuItem(item *MenuItem) {
	r.mu.Lock()
	defer r.mu.Unlock()
	r.menu = append(r.menu, *item)
}

func (r *Restaurant) RemoveMenuItem(item *MenuItem) {
	r.mu.Lock()
	defer r.mu.Unlock()
	for i, menuItem := range r.menu {
		if menuItem.ID == item.ID {
			r.menu = append(r.menu[:i], r.menu[i+1:]...)
			break
		}
	}
}

func (r *Restaurant) GetMenu() []MenuItem {
	r.mu.Lock()
	defer r.mu.Unlock()
	return r.menu
}

func (r *Restaurant) PlaceOrder(order *Order) {
	r.mu.Lock()
	defer r.mu.Unlock()
	r.orders[order.ID] = order
	r.notifyKitchen(order)
}

func (r *Restaurant) UpdateOrderStatus(orderID int, status OrderStatus) {
	r.mu.Lock()
	defer r.mu.Unlock()
	if order, exists := r.orders[orderID]; exists {
		order.SetStatus(status)
		r.notifyStaff(order)
	}
}

func (r *Restaurant) MakeReservation(reservation *Reservation) {
	r.mu.Lock()
	defer r.mu.Unlock()
	r.reservations = append(r.reservations, *reservation)
}

func (r *Restaurant) ProcessPayment(payment *Payment) {
	r.mu.Lock()
	defer r.mu.Unlock()
	r.payments[payment.ID] = payment
}

func (r *Restaurant) AddStaff(staff *Staff) {
	r.mu.Lock()
	defer r.mu.Unlock()
	r.staff = append(r.staff, *staff)
}

func (r *Restaurant) notifyKitchen(order *Order) {
	// Notify kitchen staff to prepare the order
}

func (r *Restaurant) notifyStaff(order *Order) {
	// Notify relevant staff about the order status update
}
