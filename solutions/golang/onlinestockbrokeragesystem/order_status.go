package onlinestockbrokeragesystem

type OrderStatus int

const (
	Pending OrderStatus = iota
	Executed
	Rejected
)
