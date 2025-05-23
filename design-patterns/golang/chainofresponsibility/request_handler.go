package chainofresponsibility

// RequestHandler defines the interface for request handlers in the chain
type RequestHandler interface {
	SetNext(handler RequestHandler)
	Handle(request *Request)
}
