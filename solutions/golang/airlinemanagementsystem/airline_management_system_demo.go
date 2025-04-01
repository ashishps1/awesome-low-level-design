package airlinemanagementsystem

import (
	"fmt"
	"time"
)

type Demo struct {
	system *AirlineManagementSystem
}

func NewDemo() *Demo {
	return &Demo{
		system: NewAirlineManagementSystem(),
	}
}

func Run() {
	system := NewAirlineManagementSystem()

	// Create users
	passenger1 := NewPassenger(
		"U001",
		"John Doe",
		"john@example.com",
		"1234567890",
	)

	// Create flights
	departureTime1 := time.Now().AddDate(0, 0, 1)
	arrivalTime1 := departureTime1.Add(2 * time.Hour)
	flight1 := NewFlight(
		"F001",
		"New York",
		"London",
		departureTime1,
		arrivalTime1,
	)

	departureTime2 := time.Now().AddDate(0, 0, 3)
	arrivalTime2 := departureTime2.Add(5 * time.Hour)
	flight2 := NewFlight(
		"F002",
		"Paris",
		"Tokyo",
		departureTime2,
		arrivalTime2,
	)

	system.AddFlight(flight1)
	system.AddFlight(flight2)

	// Create aircrafts
	aircraft1 := NewAircraft("A001", "Boeing 747", 300)
	aircraft2 := NewAircraft("A002", "Airbus A380", 500)

	system.AddAircraft(aircraft1)
	system.AddAircraft(aircraft2)

	// Search flights
	searchDate := time.Now().AddDate(0, 0, 1)
	searchResults := system.SearchFlights("New York", "London", searchDate)

	fmt.Println("Search Results:")
	for _, flight := range searchResults {
		fmt.Printf("Flight: %s - %s to %s\n",
			flight.FlightNumber,
			flight.Source,
			flight.Destination,
		)
	}

	// Create seat
	seat := NewSeat("25A", SeatTypeEconomy)

	// Book a flight
	booking := system.BookFlight(flight1, passenger1, seat, 100.0)
	if booking != nil {
		fmt.Printf("Booking successful. Booking ID: %s\n", booking.BookingNumber)
	} else {
		fmt.Println("Booking failed.")
	}

	// Cancel the booking
	system.CancelBooking(booking.BookingNumber)
	fmt.Println("Booking cancelled.")
}
