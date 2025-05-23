package chainofresponsibility

import "fmt"

// ValidationHandler handles validation requests
type ValidationHandler struct {
	BaseHandler
}

// Handle processes validation requests
func (h *ValidationHandler) Handle(request *Request) {
	if request.Type == "validate" {
		fmt.Printf("ValidationHandler: Processing validation request for data %s\n", request.Data)
		// Simulate validation logic
		if len(request.Data) > 0 {
			fmt.Println("ValidationHandler: Validation successful")
		} else {
			fmt.Println("ValidationHandler: Validation failed")
		}
	} else {
		h.HandleNext(request)
	}
}
