package elevatorsystem

type Request struct {
	SourceFloor      int
	DestinationFloor int
}

func NewRequest(sourceFloor, destinationFloor int) *Request {
	return &Request{
		SourceFloor:      sourceFloor,
		DestinationFloor: destinationFloor,
	}
}
