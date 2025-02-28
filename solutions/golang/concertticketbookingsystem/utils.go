package concertbookingsystem

import "fmt"

func GenerateSeats(numberOfSeats int) []*Seat {
	seats := make([]*Seat, 0, numberOfSeats)
	for i := 1; i <= numberOfSeats; i++ {
		seatNumber := fmt.Sprintf("S%d", i)
		var seatType SeatType
		var price float64

		switch {
		case i <= 10:
			seatType = SeatTypeVIP
			price = 100.0
		case i <= 30:
			seatType = SeatTypePremium
			price = 75.0
		default:
			seatType = SeatTypeRegular
			price = 50.0
		}

		seats = append(seats, NewSeat(seatNumber, seatNumber, seatType, price))
	}
	return seats
}
