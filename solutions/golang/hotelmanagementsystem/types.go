package hotelmanagement

type RoomType int
type RoomStatus int
type ReservationStatus int

const (
	RoomTypeSingle RoomType = iota
	RoomTypeDouble
	RoomTypeDeluxe
	RoomTypeSuite
)

const (
	RoomStatusAvailable RoomStatus = iota
	RoomStatusBooked
	RoomStatusOccupied
)

const (
	ReservationStatusConfirmed ReservationStatus = iota
	ReservationStatusCancelled
)
