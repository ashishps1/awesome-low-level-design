package ridesharingservice

import "fmt"

func Run() {
	rideService := GetRideService()

	// Create passengers
	passenger1 := &Passenger{ID: 1, Name: "John Doe", Contact: "1234567890", Location: &Location{Latitude: 37.7749, Longitude: -122.4194}}
	passenger2 := &Passenger{ID: 2, Name: "Jane Smith", Contact: "9876543210", Location: &Location{Latitude: 37.7860, Longitude: -122.4070}}
	rideService.AddPassenger(passenger1)
	rideService.AddPassenger(passenger2)

	// Create drivers
	driver1 := &Driver{ID: 1, Name: "Alice Johnson", Contact: "4567890123", LicensePlate: "ABC123", Location: &Location{Latitude: 37.7749, Longitude: -122.4194}, Status: Available}
	driver2 := &Driver{ID: 2, Name: "Bob Williams", Contact: "7890123456", LicensePlate: "XYZ789", Location: &Location{Latitude: 37.7860, Longitude: -122.4070}, Status: Available}
	rideService.AddDriver(driver1)
	rideService.AddDriver(driver2)

	// Passenger 1 requests a ride
	rideService.RequestRide(passenger1, passenger1.Location, &Location{Latitude: 37.7887, Longitude: -122.4098})

	// Driver 1 accepts the ride
	ride := <-rideService.requestedRides
	rideService.AcceptRide(driver1, ride)

	// Start and complete the ride
	rideService.StartRide(ride)
	rideService.CompleteRide(ride)

	// Passenger 2 requests a ride and cancels it
	rideService.RequestRide(passenger2, passenger2.Location, &Location{Latitude: 37.7749, Longitude: -122.4194})
	ride2 := <-rideService.requestedRides
	rideService.AcceptRide(driver2, ride2)
	rideService.CancelRide(ride2)

	fmt.Println("Demo completed")
}
