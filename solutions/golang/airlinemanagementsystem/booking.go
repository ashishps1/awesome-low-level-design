package airlinemanagementsystem

import "sync"

type Booking struct {
	BookingNumber string
	Flight        *Flight
	Passenger     *Passenger
	Seat          *Seat
	Price         float64
	Status        BookingStatus
	mu            sync.RWMutex
}

func NewBooking(bookingNumber string, flight *Flight, passenger *Passenger, seat *Seat, price float64) *Booking {
	return &Booking{
		BookingNumber: bookingNumber,
		Flight:        flight,
		Passenger:     passenger,
		Seat:          seat,
		Price:         price,
		Status:        BookingStatusConfirmed,
	}
}

func (b *Booking) Cancel() {
	b.mu.Lock()
	defer b.mu.Unlock()
	b.Status = BookingStatusCancelled
}
