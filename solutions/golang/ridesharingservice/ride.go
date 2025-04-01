package ridesharingservice

type Ride struct {
	ID          int
	Passenger   *Passenger
	Driver      *Driver
	Source      *Location
	Destination *Location
	Status      RideStatus
	Fare        float64
}
