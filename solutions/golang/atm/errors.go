package atm

import "errors"

var (
	ErrInsufficientFunds     = errors.New("insufficient funds in account")
	ErrInsufficientCashInATM = errors.New("insufficient cash available in ATM")
	ErrInvalidCard           = errors.New("invalid card")
	ErrInvalidPIN            = errors.New("invalid PIN")
)
