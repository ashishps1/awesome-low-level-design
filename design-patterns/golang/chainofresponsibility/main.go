package chainofresponsibility

import (
	"fmt"
)

func main() {
	// Create handlers
	auth := &AuthenticationHandler{}
	authz := &AuthorizationHandler{}
	validate := &ValidationHandler{}

	// Set up the chain
	auth.SetNext(authz)
	authz.SetNext(validate)

	// Create requests
	authRequest := &Request{
		Type: "auth",
		Data: "valid_user",
	}

	authzRequest := &Request{
		Type: "authz",
		Data: "admin_resource",
	}

	validateRequest := &Request{
		Type: "validate",
		Data: "test_data",
	}

	invalidRequest := &Request{
		Type: "unknown",
		Data: "invalid_data",
	}

	// Process requests
	fmt.Println("Processing authentication request:")
	auth.Handle(authRequest)

	fmt.Println("\nProcessing authorization request:")
	auth.Handle(authzRequest)

	fmt.Println("\nProcessing validation request:")
	auth.Handle(validateRequest)

	fmt.Println("\nProcessing invalid request:")
	auth.Handle(invalidRequest)
}
