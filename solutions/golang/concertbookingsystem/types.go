package concertbookingsystem

type SeatType int
type SeatStatus int
type BookingStatus int

const (
	SeatTypeRegular SeatType = iota
	SeatTypePremium
	SeatTypeVIP
)

const (
	StatusAvailable SeatStatus = iota
	StatusBooked
	StatusReserved
)

const (
	BookingStatusPending BookingStatus = iota
	BookingStatusConfirmed
	BookingStatusCancelled
)
