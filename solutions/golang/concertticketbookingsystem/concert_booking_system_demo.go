package concertbookingsystem

import (
	"fmt"
	"time"
)

func Run() {
	bookingSystem := GetBookingSystem()

	// Create concerts
	concert1Seats := GenerateSeats(100)
	concert1 := NewConcert("C001", "Artist 1", "Venue 1",
		time.Now().Add(30*24*time.Hour), concert1Seats)
	bookingSystem.AddConcert(concert1)

	concert2Seats := GenerateSeats(50)
	concert2 := NewConcert("C002", "Artist 2", "Venue 2",
		time.Now().Add(60*24*time.Hour), concert2Seats)
	bookingSystem.AddConcert(concert2)

	// Create users
	user1 := NewUser("U001", "John Doe", "john@example.com")
	user2 := NewUser("U002", "Jane Smith", "jane@example.com")

	// Search concerts
	searchResults := bookingSystem.SearchConcerts("Artist 1", "Venue 1",
		time.Now().Add(30*24*time.Hour))

	fmt.Println("Search Results:")
	for _, concert := range searchResults {
		fmt.Printf("Concert: %s at %s\n", concert.Artist, concert.Venue)
	}

	// Book tickets
	selectedSeats1 := concert1.Seats[:3] // Select first 3 seats
	booking1, err := bookingSystem.BookTickets(user1, concert1, selectedSeats1)
	if err != nil {
		fmt.Printf("Booking error: %v\n", err)
	}

	selectedSeats2 := concert2.Seats[:2] // Select first 2 seats
	booking2, err := bookingSystem.BookTickets(user2, concert2, selectedSeats2)
	if err != nil {
		fmt.Printf("Booking error: %v\n", err)
	}

	if booking2 != nil {
		fmt.Printf("Booking Successful\n")
	}

	// Cancel booking
	if booking1 != nil {
		bookingSystem.CancelBooking(booking1.ID)
	}

	// Book tickets again
	selectedSeats3 := concert1.Seats[3:5] // Select next 2 seats
	booking3, err := bookingSystem.BookTickets(user2, concert1, selectedSeats3)
	if err != nil {
		fmt.Printf("Booking error: %v\n", err)
	}

	if booking3 != nil {
		fmt.Printf("Booking Successful\n")
	}
}
