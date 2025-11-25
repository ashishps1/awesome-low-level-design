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

	// Hold seats for the user
	for _, seat := range seats {
		if err := seat.Hold(time.Minute); err != nil {
			// Rollback previous bookings
			for _, s := range seats {
				if s == seat {
					break
				}
				s.Release()
			}
			return nil, err
		}
		concert.LockManager.AddSeatLock(seat, 5*time.Minute)
	}

	// Create booking
	bookingID := fmt.Sprintf("BKG-%d", time.Now().UnixNano())
	booking := NewBooking(bookingID, user, concert, seats)

	// Process payment (mock)
	bs.processPayment(booking)

	// Confirm booking
	err := booking.ConfirmBooking()
	if err != nil {
		// Rollback seat bookings to reserved, ensuring failures do not free seats, so they can be retried
		for _, seat := range seats {
			seat.status = StatusReserved
		}
		return nil, err
	}

	// Store booking
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

func (bs *ConcertTicketBookingSystem) StartLockReleaser(concertId string) {
	go func() {
		ticker := time.NewTicker(time.Second)
		for range ticker.C {
			concert := bs.concerts[concertId]
			if concert != nil {
				concert.LockManager.ReleaseExpiredLocks()
			}
		}
	}()
}
