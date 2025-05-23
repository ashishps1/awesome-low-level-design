package main

import (
	"design-patterns/golang/builder"
	"fmt"
)

func main() {
	// Create a GET request
	getRequest, err := builder.NewHttpRequestBuilder("https://api.example.com/users")
	if err != nil {
		fmt.Printf("Error creating request: %v\n", err)
		return
	}

	getRequest.
		Method("GET").
		Header("Accept", "application/json").
		QueryParam("page", "1").
		QueryParam("limit", "10").
		Timeout(5000)

	request := getRequest.Build()
	fmt.Println("GET Request:", request)

	// Create a POST request
	postRequest, err := builder.NewHttpRequestBuilder("https://api.example.com/users")
	if err != nil {
		fmt.Printf("Error creating request: %v\n", err)
		return
	}

	postRequest.
		Method("POST").
		Header("Content-Type", "application/json").
		Header("Authorization", "Bearer token123").
		Body(`{"name": "John Doe", "email": "john@example.com"}`).
		Timeout(10000)

	request = postRequest.Build()
	fmt.Println("\nPOST Request:", request)
}
