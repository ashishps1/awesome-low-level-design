package movieticketbookingsystem

type SeatType int
type SeatStatus int
type BookingStatus int

const (
	SeatTypeNormal SeatType = iota
	SeatTypePremium
)

const (
	SeatStatusAvailable SeatStatus = iota
	SeatStatusBooked
)

const (
	BookingStatusPending BookingStatus = iota
	BookingStatusConfirmed
	BookingStatusCancelled
)
