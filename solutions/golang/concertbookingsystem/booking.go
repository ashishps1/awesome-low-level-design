package concertbookingsystem

type Booking struct {
	ID         string
	User       *User
	Concert    *Concert
	Seats      []*Seat
	TotalPrice float64
	Status     BookingStatus
}

func NewBooking(id string, user *User, concert *Concert, seats []*Seat) *Booking {
	totalPrice := calculateTotalPrice(seats)
	return &Booking{
		ID:         id,
		User:       user,
		Concert:    concert,
		Seats:      seats,
		TotalPrice: totalPrice,
		Status:     BookingStatusPending,
	}
}

func (b *Booking) ConfirmBooking() {
	if b.Status == BookingStatusPending {
		b.Status = BookingStatusConfirmed
		// TODO: Send booking confirmation to user
	}
}

func (b *Booking) CancelBooking() {
	if b.Status == BookingStatusConfirmed {
		b.Status = BookingStatusCancelled
		for _, seat := range b.Seats {
			seat.Release()
		}
		// TODO: Send cancellation notification to user
	}
}

func calculateTotalPrice(seats []*Seat) float64 {
	var total float64
	for _, seat := range seats {
		total += seat.Price
	}
	return total
}
