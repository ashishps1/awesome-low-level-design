package digitalwallet

type InsufficientFundsError struct {
	message string
}

func NewInsufficientFundsError(message string) *InsufficientFundsError {
	return &InsufficientFundsError{message: message}
}

func (e *InsufficientFundsError) Error() string {
	return e.message
}
