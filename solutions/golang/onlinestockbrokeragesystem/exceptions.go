package onlinestockbrokeragesystem

type InsufficientFundsException struct {
	message string
}

func (e *InsufficientFundsException) Error() string {
	return e.message
}

type InsufficientStockException struct {
	message string
}

func (e *InsufficientStockException) Error() string {
	return e.message
}

func NewInsufficientStockException(message string) *InsufficientStockException {
	return &InsufficientStockException{message: message}
}
