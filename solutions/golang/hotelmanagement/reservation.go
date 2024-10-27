package hotelmanagement

import (
	"fmt"
	"sync"
	"time"
)

type Reservation struct {
	ID           string
	Guest        *Guest
	Room         *Room
	CheckInDate  time.Time
	CheckOutDate time.Time
	Status       ReservationStatus
	mu           sync.RWMutex
}

func NewReservation(id string, guest *Guest, room *Room, checkInDate, checkOutDate time.Time) *Reservation {
	return &Reservation{
		ID:           id,
		Guest:        guest,
		Room:         room,
		CheckInDate:  checkInDate,
		CheckOutDate: checkOutDate,
		Status:       ReservationStatusConfirmed,
	}
}

func (r *Reservation) Cancel() error {
	r.mu.Lock()
	defer r.mu.Unlock()

	if r.Status != ReservationStatusConfirmed {
		return fmt.Errorf("reservation is not confirmed")
	}

	r.Status = ReservationStatusCancelled
	return r.Room.CheckOut()
}
