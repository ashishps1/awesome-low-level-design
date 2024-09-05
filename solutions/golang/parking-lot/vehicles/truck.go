package vehicles

type Truck struct {
	vehicleBase
}

func NewTruck(regNo string) *Truck {
	return &Truck{vehicleBase{
		RegistrationNo: regNo,
		VehicleType:    TRUCK,
	}}
}

func (c *Truck) Cost() int {
	return 30
}
