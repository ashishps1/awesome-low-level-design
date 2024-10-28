package airlinemanagementsystem

import (
	"fmt"
	"sync"
	"sync/atomic"
	"time"
)

type BookingManager struct {
	bookings       map[string]*Booking
	bookingCounter int64
	mu             sync.RWMutex
}

var (
	bookingManager *BookingManager
	bookingOnce    sync.Once
)

func GetBookingManager() *BookingManager {
	bookingOnce.Do(func() {
		bookingManager = &BookingManager{
			bookings: make(map[string]*Booking),
		}
	})
	return bookingManager
}

func (bm *BookingManager) CreateBooking(flight *Flight, passenger *Passenger, seat *Seat, price float64) *Booking {
	bm.mu.Lock()
	defer bm.mu.Unlock()

	bookingNumber := bm.generateBookingNumber()
	booking := NewBooking(bookingNumber, flight, passenger, seat, price)
	bm.bookings[bookingNumber] = booking
	return booking
}

func (bm *BookingManager) CancelBooking(bookingNumber string) {
	bm.mu.Lock()
	defer bm.mu.Unlock()

	if booking, exists := bm.bookings[bookingNumber]; exists {
		booking.Cancel()
	}
}

func (bm *BookingManager) generateBookingNumber() string {
	counter := atomic.AddInt64(&bm.bookingCounter, 1)
	return fmt.Sprintf("BKG%s%06d",
		time.Now().Format("20060102150405"),
		counter)
}
