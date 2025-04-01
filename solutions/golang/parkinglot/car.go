package parkinglot

func NewCar(licensePlate string) Vehicle {
	return &BaseVehicle{licensePlate: licensePlate, vehicleType: CAR}
}
