package vehicles

type Car struct {
	vehicleBase
}

func NewCar(regNo string) *Car {
	return &Car{vehicleBase{
		RegistrationNo: regNo,
		VehicleType:    CAR,
	}}
}

func (c *Car) Cost() int {
	return 20
}
