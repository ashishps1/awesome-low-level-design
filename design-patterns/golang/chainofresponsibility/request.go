package chainofresponsibility

// Request represents a request in the chain
type Request struct {
	Type string
	Data string
}

// NewRequest creates a new Request
func NewRequest(user, role string, requestCount int, payload string) *Request {
	return &Request{
		User:         user,
		UserRole:     role,
		RequestCount: requestCount,
		Payload:      payload,
	}
}
