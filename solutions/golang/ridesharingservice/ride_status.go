package ridesharingservice

type RideStatus int

const (
	Requested RideStatus = iota
	Accepted
	InProgress
	Completed
	Cancelled
)
