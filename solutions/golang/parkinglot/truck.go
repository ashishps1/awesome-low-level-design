package parkinglot

func NewTruck(licensePlate string) Vehicle {
	return &BaseVehicle{licensePlate: licensePlate, vehicleType: TRUCK}
}
