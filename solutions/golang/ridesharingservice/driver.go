package ridesharingservice

type Driver struct {
	ID           int
	Name         string
	Contact      string
	LicensePlate string
	Location     *Location
	Status       DriverStatus
}
