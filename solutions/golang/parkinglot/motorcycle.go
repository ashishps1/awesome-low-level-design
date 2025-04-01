package parkinglot

func NewMotorcycle(licensePlate string) Vehicle {
	return &BaseVehicle{licensePlate: licensePlate, vehicleType: MOTORCYCLE}
}
