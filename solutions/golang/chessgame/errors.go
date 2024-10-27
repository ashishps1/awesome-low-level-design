package chessgame

type InvalidMoveError struct {
	message string
}

func NewInvalidMoveError(message string) *InvalidMoveError {
	return &InvalidMoveError{message: message}
}

func (e *InvalidMoveError) Error() string {
	return e.message
}
