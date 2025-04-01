package movieticketbookingsystem

import "sync"

type Booking struct {
	ID         string
	User       *User
	Show       *Show
	Seats      []*Seat
	TotalPrice float64
	Status     BookingStatus
	mu         sync.RWMutex
}

func NewBooking(id string, user *User, show *Show, seats []*Seat, totalPrice float64, status BookingStatus) *Booking {
	return &Booking{
		ID:         id,
		User:       user,
		Show:       show,
		Seats:      seats,
		TotalPrice: totalPrice,
		Status:     status,
	}
}

func (b *Booking) GetStatus() BookingStatus {
	b.mu.RLock()
	defer b.mu.RUnlock()
	return b.Status
}

func (b *Booking) SetStatus(status BookingStatus) {
	b.mu.Lock()
	defer b.mu.Unlock()
	b.Status = status
}
