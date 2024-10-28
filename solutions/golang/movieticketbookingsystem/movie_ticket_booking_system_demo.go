package movieticketbookingsystem

import (
	"fmt"
	"time"
)

func Run() {
	bookingSystem := GetBookingSystem()

	// Add movies
	movie1 := NewMovie("M1", "Movie 1", "Description 1", 120)
	movie2 := NewMovie("M2", "Movie 2", "Description 2", 135)
	bookingSystem.AddMovie(movie1)
	bookingSystem.AddMovie(movie2)

	// Add theaters
	theater1 := NewTheater("T1", "Theater 1", "Location 1")
	theater2 := NewTheater("T2", "Theater 2", "Location 2")
	bookingSystem.AddTheater(theater1)
	bookingSystem.AddTheater(theater2)

	// Add shows
	show1 := NewShow(
		"S1",
		movie1,
		theater1,
		time.Now(),
		time.Now().Add(time.Duration(movie1.DurationMinutes)*time.Minute),
		CreateSeats(10, 10),
	)
	show2 := NewShow(
		"S2",
		movie2,
		theater2,
		time.Now(),
		time.Now().Add(time.Duration(movie2.DurationMinutes)*time.Minute),
		CreateSeats(8, 8),
	)

	bookingSystem.AddShow(show1)
	bookingSystem.AddShow(show2)

	// Create user
	user := NewUser("U1", "John Doe", "john@example.com")

	// Select seats
	selectedSeats := []*Seat{
		show1.Seats["1-5"],
		show1.Seats["1-6"],
	}

	// Book tickets
	booking, err := bookingSystem.BookTickets(user, show1, selectedSeats)
	if err != nil {
		fmt.Printf("Booking failed: %v\n", err)
		return
	}

	fmt.Printf("Booking successful. Booking ID: %s\n", booking.ID)

	// Confirm booking
	if err := bookingSystem.ConfirmBooking(booking.ID); err != nil {
		fmt.Printf("Failed to confirm booking: %v\n", err)
		return
	}
	fmt.Println("Booking confirmed")

	// Cancel booking
	if err := bookingSystem.CancelBooking(booking.ID); err != nil {
		fmt.Printf("Failed to cancel booking: %v\n", err)
		return
	}
	fmt.Printf("Booking canceled. Booking ID: %s\n", booking.ID)
}
