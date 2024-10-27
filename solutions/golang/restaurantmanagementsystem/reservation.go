package restaurantmanagementsystem

import (
	"time"
)

type Reservation struct {
	ID              int
	CustomerName    string
	ContactNumber   string
	PartySize       int
	ReservationTime time.Time
}

func NewReservation(id int, customerName, contactNumber string, partySize int, reservationTime time.Time) *Reservation {
	return &Reservation{
		ID:              id,
		CustomerName:    customerName,
		ContactNumber:   contactNumber,
		PartySize:       partySize,
		ReservationTime: reservationTime,
	}
}
