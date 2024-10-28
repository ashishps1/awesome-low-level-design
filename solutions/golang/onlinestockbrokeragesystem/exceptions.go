package onlinestockbrokeragesystem

type InsufficientFundsError struct {
	message string
}

func NewInsufficientFundsError(message string) *InsufficientFundsError {
	return &InsufficientFundsError{message: message}
}

func (e *InsufficientFundsError) Error() string {
	return e.message
}

type InsufficientStockError struct {
	message string
}

func NewInsufficientStockError(message string) *InsufficientStockError {
	return &InsufficientStockError{message: message}
}

func (e *InsufficientStockError) Error() string {
	return e.message
}
