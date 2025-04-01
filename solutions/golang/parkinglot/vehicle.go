package parkinglot

type VehicleType int

const (
	CAR VehicleType = iota
	MOTORCYCLE
	TRUCK
)

type Vehicle interface {
	GetLicensePlate() string
	GetType() VehicleType
}

type BaseVehicle struct {
	licensePlate string
	vehicleType  VehicleType
}

func (v *BaseVehicle) GetLicensePlate() string {
	return v.licensePlate
}

func (v *BaseVehicle) GetType() VehicleType {
	return v.vehicleType
}
