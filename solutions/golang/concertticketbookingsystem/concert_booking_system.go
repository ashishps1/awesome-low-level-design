package concertbookingsystem

import (
	"fmt"
	"sync"
	"time"
)

type ConcertTicketBookingSystem struct {
	concerts map[string]*Concert
	bookings map[string]*Booking
	mu       sync.Mutex
}

var (
	instance *ConcertTicketBookingSystem
	once     sync.Once
)

func GetBookingSystem() *ConcertTicketBookingSystem {
	once.Do(func() {
		instance = &ConcertTicketBookingSystem{
			concerts: make(map[string]*Concert),
			bookings: make(map[string]*Booking),
		}
	})
	return instance
}

func (bs *ConcertTicketBookingSystem) AddConcert(concert *Concert) {
	bs.mu.Lock()
	defer bs.mu.Unlock()
	bs.concerts[concert.ID] = concert
}

func (bs *ConcertTicketBookingSystem) GetConcert(concertID string) *Concert {
	bs.mu.Lock()
	defer bs.mu.Unlock()
	return bs.concerts[concertID]
}

func (bs *ConcertTicketBookingSystem) SearchConcerts(artist, venue string, dateTime time.Time) []*Concert {
	bs.mu.Lock()
	defer bs.mu.Unlock()

	var results []*Concert
	for _, concert := range bs.concerts {
		if concert.Artist == artist &&
			concert.Venue == venue &&
			concert.DateTime.Equal(dateTime) {
			results = append(results, concert)
		}
	}
	return results
}

func (bs *ConcertTicketBookingSystem) BookTickets(user *User, concert *Concert, seats []*Seat) (*Booking, error) {
	bs.mu.Lock()
	defer bs.mu.Unlock()

	// Check seat availability
	for _, seat := range seats {
		if seat.GetStatus() != StatusAvailable {
			return nil, NewSeatNotAvailableError(fmt.Sprintf("Seat %s is not available", seat.SeatNumber))
		}
	}

	// Book seats
	for _, seat := range seats {
		if err := seat.Book(); err != nil {
			// Rollback previous bookings
			for _, s := range seats {
				if s == seat {
					break
				}
				s.Release()
			}
			return nil, err
		}
	}

	// Create booking
	bookingID := fmt.Sprintf("BKG-%d", time.Now().UnixNano())
	booking := NewBooking(bookingID, user, concert, seats)

	// Process payment (mock)
	bs.processPayment(booking)

	// Confirm booking
	booking.ConfirmBooking()
	bs.bookings[bookingID] = booking

	fmt.Printf("Booking %s - %d seats booked\n", booking.ID, len(booking.Seats))
	return booking, nil
}

func (bs *ConcertTicketBookingSystem) CancelBooking(bookingID string) {
	bs.mu.Lock()
	defer bs.mu.Unlock()

	if booking, exists := bs.bookings[bookingID]; exists {
		booking.CancelBooking()
		delete(bs.bookings, bookingID)
		fmt.Printf("Booking %s cancelled\n", bookingID)
	}
}

func (bs *ConcertTicketBookingSystem) processPayment(booking *Booking) {
	// Mock payment processing
}
