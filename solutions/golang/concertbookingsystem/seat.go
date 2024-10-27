package concertbookingsystem

import "sync"

type Seat struct {
	ID         string
	SeatNumber string
	Type       SeatType
	Price      float64
	status     SeatStatus
	mu         sync.Mutex
}

func NewSeat(id, seatNumber string, seatType SeatType, price float64) *Seat {
	return &Seat{
		ID:         id,
		SeatNumber: seatNumber,
		Type:       seatType,
		Price:      price,
		status:     StatusAvailable,
	}
}

func (s *Seat) Book() error {
	s.mu.Lock()
	defer s.mu.Unlock()

	if s.status != StatusAvailable {
		return NewSeatNotAvailableError("Seat is already booked or reserved")
	}
	s.status = StatusBooked
	return nil
}

func (s *Seat) Release() {
	s.mu.Lock()
	defer s.mu.Unlock()

	if s.status == StatusBooked {
		s.status = StatusAvailable
	}
}

func (s *Seat) GetStatus() SeatStatus {
	s.mu.Lock()
	defer s.mu.Unlock()
	return s.status
}
