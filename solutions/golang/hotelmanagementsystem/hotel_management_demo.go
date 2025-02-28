package hotelmanagement

import (
	"fmt"
	"time"
)

func Run() {
	hotelSystem := GetHotelManagementSystem()

	// Create guests
	guest1 := NewGuest("G001", "John Doe", "john@example.com", "1234567890")
	guest2 := NewGuest("G002", "Jane Smith", "jane@example.com", "9876543210")
	hotelSystem.AddGuest(guest1)
	hotelSystem.AddGuest(guest2)

	// Create rooms
	room1 := NewRoom("R001", RoomTypeSingle, 100.0)
	room2 := NewRoom("R002", RoomTypeDouble, 200.0)
	hotelSystem.AddRoom(room1)
	hotelSystem.AddRoom(room2)

	// Book a room
	checkInDate := time.Now()
	checkOutDate := checkInDate.AddDate(0, 0, 3)

	reservation1, err := hotelSystem.BookRoom(guest1, room1, checkInDate, checkOutDate)
	if err != nil {
		fmt.Printf("Failed to book room: %v\n", err)
		return
	}
	fmt.Printf("Reservation created: %s\n", reservation1.ID)

	// Check-in
	if err := hotelSystem.CheckIn(reservation1.ID); err != nil {
		fmt.Printf("Failed to check in: %v\n", err)
		return
	}
	fmt.Printf("Checked in: %s\n", reservation1.ID)

	// Check-out and process payment
	payment := NewCreditCardPayment()
	if err := hotelSystem.CheckOut(reservation1.ID, payment); err != nil {
		fmt.Printf("Failed to check out: %v\n", err)
		return
	}
	fmt.Printf("Checked out: %s\n", reservation1.ID)

	// Cancel a reservation
	if err := hotelSystem.CancelReservation(reservation1.ID); err != nil {
		fmt.Printf("Failed to cancel reservation: %v\n", err)
		return
	}
	fmt.Printf("Reservation cancelled: %s\n", reservation1.ID)
}
