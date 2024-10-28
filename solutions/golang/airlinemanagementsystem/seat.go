package airlinemanagementsystem

import "sync"

type Seat struct {
	SeatNumber string
	Type       SeatType
	status     SeatStatus
	mu         sync.RWMutex
}

func NewSeat(seatNumber string, seatType SeatType) *Seat {
	return &Seat{
		SeatNumber: seatNumber,
		Type:       seatType,
		status:     SeatStatusAvailable,
	}
}

func (s *Seat) Reserve() {
	s.mu.Lock()
	defer s.mu.Unlock()
	s.status = SeatStatusReserved
}

func (s *Seat) Release() {
	s.mu.Lock()
	defer s.mu.Unlock()
	s.status = SeatStatusAvailable
}

func (s *Seat) GetStatus() SeatStatus {
	s.mu.RLock()
	defer s.mu.RUnlock()
	return s.status
}
