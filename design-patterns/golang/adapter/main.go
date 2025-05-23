package main

import (
	"design-patterns/golang/adapter"
	"fmt"
)

func main() {
	// Using the in-house payment processor
	fmt.Println("Using In-House Payment Processor:")
	inHouseProcessor := &adapter.InHousePaymentProcessor{}
	checkoutService := adapter.NewCheckoutService(inHouseProcessor)
	checkoutService.ProcessCheckout(100.0, "USD")

	fmt.Println("\nUsing Legacy Gateway (via Adapter):")
	// Using the legacy gateway through the adapter
	legacyGateway := &adapter.LegacyGateway{}
	legacyAdapter := adapter.NewLegacyGatewayAdapter(legacyGateway)
	checkoutService = adapter.NewCheckoutService(legacyAdapter)
	checkoutService.ProcessCheckout(150.0, "EUR")
}
