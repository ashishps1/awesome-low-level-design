package vehicles

type Bike struct {
	vehicleBase
}

func NewBike(regNo string) *Bike {
	return &Bike{vehicleBase{
		RegistrationNo: regNo,
		VehicleType:    BIKE,
	}}
}

func (c *Bike) Cost() int {
	return 10
}
