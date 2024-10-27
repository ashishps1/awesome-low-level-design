package movieticketbookingsystem

import (
	"fmt"
	"time"
)

type Demo struct {
	bookingSystem *MovieTicketBookingSystem
}

func NewDemo() *Demo {
	return &Demo{
		bookingSystem: GetBookingSystem(),
	}
}

func (d *Demo) Run() {
	// Add movies
	movie1 := NewMovie("M1", "Movie 1", "Description 1", 120)
	movie2 := NewMovie("M2", "Movie 2", "Description 2", 135)
	d.bookingSystem.AddMovie(movie1)
	d.bookingSystem.AddMovie(movie2)

	// Add theaters
	theater1 := NewTheater("T1", "Theater 1", "Location 1", nil)
	theater2 := NewTheater("T2", "Theater 2", "Location 2", nil)
	d.bookingSystem.AddTheater(theater1)
	d.bookingSystem.AddTheater(theater2)

	// Add shows
	now := time.Now()
	show1 := NewShow(
		"S1",
		movie1,
		theater1,
		now,
		now.Add(time.Duration(movie1.DurationMinutes)*time.Minute),
		d.createSeats(10, 10),
	)
	show2 := NewShow(
		"S2",
		movie2,
		theater2,
		now,
		now.Add(time.Duration(movie2.DurationMinutes)*time.Minute),
		d.createSeats(8, 8),
	)
	d.bookingSystem.AddShow(show1)
	d.bookingSystem.AddShow(show2)

	// Book tickets
	user := NewUser("U1", "John Doe", "john@example.com")
	selectedSeats := []*Seat{
		show1.Seats["1-5"],
		show1.Seats["1-6"],
	}

	fmt.Println("Attempting to book tickets...")
	reservation, err := d.bookingSystem.BookTickets(user, show1, selectedSeats)
	if err != nil {
		fmt.Printf("Booking failed: %v\n", err)
		return
	}

	fmt.Printf("Booking successful. Booking ID: %s\n", reservation.ID)

	fmt.Println("\nConfirming booking...")
	if err := d.bookingSystem.ConfirmBooking(reservation.ID); err != nil {
		fmt.Printf("Failed to confirm booking: %v\n", err)
		return
	}
	fmt.Println("Booking confirmed successfully")

	fmt.Println("\nCancelling booking...")
	if err := d.bookingSystem.CancelBooking(reservation.ID); err != nil {
		fmt.Printf("Failed to cancel booking: %v\n", err)
		return
	}
	fmt.Printf("Booking canceled. Booking ID: %s\n", reservation.ID)
}

func (d *Demo) createSeats(rows, columns int) map[string]*Seat {
	seats := make(map[string]*Seat)
	for row := 1; row <= rows; row++ {
		for col := 1; col <= columns; col++ {
			seatID := fmt.Sprintf("%d-%d", row, col)
			seatType := SeatTypeNormal
			price := 100.0

			if row <= 2 {
				seatType = SeatTypePremium
				price = 150.0
			}

			seats[seatID] = NewSeat(
				seatID,
				row,
				col,
				seatType,
				price,
				SeatStatusAvailable,
			)
		}
	}
	return seats
}
