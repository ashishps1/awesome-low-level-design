package chainofresponsibility

import "fmt"

// AuthenticationHandler handles authentication requests
type AuthenticationHandler struct {
	BaseHandler
}

// Handle processes authentication requests
func (h *AuthenticationHandler) Handle(request *Request) {
	if request.Type == "auth" {
		fmt.Printf("AuthenticationHandler: Processing authentication request for user %s\n", request.Data)
		// Simulate authentication logic
		if request.Data == "valid_user" {
			fmt.Println("AuthenticationHandler: Authentication successful")
		} else {
			fmt.Println("AuthenticationHandler: Authentication failed")
		}
	} else {
		h.HandleNext(request)
	}
}
