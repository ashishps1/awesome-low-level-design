package concertbookingsystem

type SeatNotAvailableError struct {
	message string
}

func NewSeatNotAvailableError(message string) *SeatNotAvailableError {
	return &SeatNotAvailableError{message: message}
}

func (e *SeatNotAvailableError) Error() string {
	return e.message
}
