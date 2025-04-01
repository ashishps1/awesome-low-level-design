package carrentalsystem

import (
	"time"
)

type Reservation struct {
	ReservationID string
	Customer      *Customer
	Car           *Car
	StartDate     time.Time
	EndDate       time.Time
	TotalPrice    float64
}

func NewReservation(reservationID string, customer *Customer, car *Car, startDate, endDate time.Time) *Reservation {
	res := &Reservation{
		ReservationID: reservationID,
		Customer:      customer,
		Car:           car,
		StartDate:     startDate,
		EndDate:       endDate,
	}
	res.TotalPrice = res.calculateTotalPrice()
	return res
}

func (r *Reservation) calculateTotalPrice() float64 {
	days := r.EndDate.Sub(r.StartDate).Hours() / 24
	return r.Car.RentalPricePerDay * days
}
