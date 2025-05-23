package chainofresponsibility

// BaseHandler provides common functionality for request handlers
type BaseHandler struct {
	next RequestHandler
}

// SetNext sets the next handler in the chain
func (h *BaseHandler) SetNext(handler RequestHandler) {
	h.next = handler
}

// HandleNext passes the request to the next handler if one exists
func (h *BaseHandler) HandleNext(request *Request) {
	if h.next != nil {
		h.next.Handle(request)
	}
}
