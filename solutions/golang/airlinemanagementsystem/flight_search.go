package airlinemanagementsystem

import (
	"strings"
	"sync"
	"time"
)

type FlightSearch struct {
	flights []*Flight
	mu      sync.RWMutex
}

func NewFlightSearch(flights []*Flight) *FlightSearch {
	return &FlightSearch{
		flights: flights,
	}
}

func (fs *FlightSearch) SearchFlights(source, destination string, date time.Time) []*Flight {
	fs.mu.RLock()
	defer fs.mu.RUnlock()

	var results []*Flight
	source = strings.ToLower(source)
	destination = strings.ToLower(destination)

	for _, flight := range fs.flights {
		if strings.ToLower(flight.Source) == source &&
			strings.ToLower(flight.Destination) == destination &&
			flight.DepartureTime.Year() == date.Year() &&
			flight.DepartureTime.Month() == date.Month() &&
			flight.DepartureTime.Day() == date.Day() {
			results = append(results, flight)
		}
	}
	return results
}
