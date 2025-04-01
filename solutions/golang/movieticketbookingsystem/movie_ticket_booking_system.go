package movieticketbookingsystem

import (
	"fmt"
	"sync"
	"sync/atomic"
	"time"
)

type MovieTicketBookingSystem struct {
	movies       []*Movie
	theaters     []*Theater
	shows        map[string]*Show
	bookings     map[string]*Booking
	mu           sync.RWMutex
	bookingCount int64
}

var (
	instance *MovieTicketBookingSystem
	once     sync.Once
)

func GetBookingSystem() *MovieTicketBookingSystem {
	once.Do(func() {
		instance = &MovieTicketBookingSystem{
			movies:   make([]*Movie, 0),
			theaters: make([]*Theater, 0),
			shows:    make(map[string]*Show),
			bookings: make(map[string]*Booking),
		}
	})
	return instance
}

func (bs *MovieTicketBookingSystem) AddMovie(movie *Movie) {
	bs.mu.Lock()
	defer bs.mu.Unlock()
	bs.movies = append(bs.movies, movie)
}

func (bs *MovieTicketBookingSystem) AddTheater(theater *Theater) {
	bs.mu.Lock()
	defer bs.mu.Unlock()
	bs.theaters = append(bs.theaters, theater)
}

func (bs *MovieTicketBookingSystem) AddShow(show *Show) {
	bs.mu.Lock()
	defer bs.mu.Unlock()
	bs.shows[show.ID] = show
}

func (bs *MovieTicketBookingSystem) GetShow(showID string) *Show {
	bs.mu.RLock()
	defer bs.mu.RUnlock()
	return bs.shows[showID]
}

func (bs *MovieTicketBookingSystem) BookTickets(user *User, show *Show, selectedSeats []*Seat) (*Booking, error) {
	bs.mu.Lock()
	defer bs.mu.Unlock()

	// Check seat availability
	for _, seat := range selectedSeats {
		showSeat, exists := show.Seats[seat.ID]
		if !exists || showSeat.GetStatus() != SeatStatusAvailable {
			return nil, fmt.Errorf("seat %s is not available", seat.ID)
		}
	}

	// Mark seats as booked
	for _, seat := range selectedSeats {
		show.Seats[seat.ID].SetStatus(SeatStatusBooked)
	}

	// Calculate total price
	var totalPrice float64
	for _, seat := range selectedSeats {
		totalPrice += seat.GetPrice()
	}

	// Generate booking ID
	bookingID := bs.generateBookingID()

	// Create booking
	booking := NewBooking(bookingID, user, show, selectedSeats, totalPrice, BookingStatusPending)
	bs.bookings[bookingID] = booking

	return booking, nil
}

func (bs *MovieTicketBookingSystem) ConfirmBooking(bookingID string) error {
	bs.mu.Lock()
	defer bs.mu.Unlock()

	booking, exists := bs.bookings[bookingID]
	if !exists {
		return fmt.Errorf("booking not found")
	}

	if booking.GetStatus() != BookingStatusPending {
		return fmt.Errorf("booking is not in pending state")
	}

	booking.SetStatus(BookingStatusConfirmed)
	return nil
}

func (bs *MovieTicketBookingSystem) CancelBooking(bookingID string) error {
	bs.mu.Lock()
	defer bs.mu.Unlock()

	booking, exists := bs.bookings[bookingID]
	if !exists {
		return fmt.Errorf("booking not found")
	}

	if booking.GetStatus() == BookingStatusCancelled {
		return fmt.Errorf("booking is already cancelled")
	}

	booking.SetStatus(BookingStatusCancelled)

	// Release seats
	for _, seat := range booking.Seats {
		booking.Show.Seats[seat.ID].SetStatus(SeatStatusAvailable)
	}

	return nil
}

func (bs *MovieTicketBookingSystem) generateBookingID() string {
	count := atomic.AddInt64(&bs.bookingCount, 1)
	return fmt.Sprintf("BKG%s%06d", time.Now().Format("20060102150405"), count)
}

// Create utility function for demo
func CreateSeats(rows, columns int) map[string]*Seat {
	seats := make(map[string]*Seat)
	for row := 1; row <= rows; row++ {
		for col := 1; col <= columns; col++ {
			seatID := fmt.Sprintf("%d-%d", row, col)
			seatType := SeatTypeNormal
			price := 100.0

			if row <= 2 {
				seatType = SeatTypePremium
				price = 150.0
			}

			seats[seatID] = NewSeat(
				seatID,
				row,
				col,
				seatType,
				price,
				SeatStatusAvailable,
			)
		}
	}
	return seats
}
