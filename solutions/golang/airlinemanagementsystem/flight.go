package airlinemanagementsystem

import (
	"sync"
	"time"
)

type Flight struct {
	FlightNumber   string
	Source         string
	Destination    string
	DepartureTime  time.Time
	ArrivalTime    time.Time
	AvailableSeats []*Seat
	mu             sync.RWMutex
}

func NewFlight(flightNumber, source, destination string, departureTime, arrivalTime time.Time) *Flight {
	return &Flight{
		FlightNumber:   flightNumber,
		Source:         source,
		Destination:    destination,
		DepartureTime:  departureTime,
		ArrivalTime:    arrivalTime,
		AvailableSeats: make([]*Seat, 0),
	}
}
