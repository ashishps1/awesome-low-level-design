package airlinemanagementsystem

type SeatType int
type SeatStatus int
type BookingStatus int
type PaymentStatus int

const (
	SeatTypeEconomy SeatType = iota
	SeatTypePremiumEconomy
	SeatTypeBusiness
	SeatTypeFirstClass
)

const (
	SeatStatusAvailable SeatStatus = iota
	SeatStatusReserved
	SeatStatusOccupied
)

const (
	BookingStatusConfirmed BookingStatus = iota
	BookingStatusCancelled
	BookingStatusPending
	BookingStatusExpired
)

const (
	PaymentStatusPending PaymentStatus = iota
	PaymentStatusCompleted
	PaymentStatusFailed
	PaymentStatusRefunded
)
