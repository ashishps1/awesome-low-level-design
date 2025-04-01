package parkinglot

type ParkingSpot struct {
	spotNumber    int
	vehicleType   VehicleType
	parkedVehicle Vehicle
}

func NewParkingSpot(spotNumber int, vehicleType VehicleType) *ParkingSpot {
	return &ParkingSpot{spotNumber: spotNumber, vehicleType: vehicleType}
}

func (ps *ParkingSpot) IsAvailable() bool {
	return ps.parkedVehicle == nil
}

func (ps *ParkingSpot) ParkVehicle(vehicle Vehicle) {
	if ps.IsAvailable() && vehicle.GetType() == ps.vehicleType {
		ps.parkedVehicle = vehicle
	}
}

func (ps *ParkingSpot) UnparkVehicle() {
	ps.parkedVehicle = nil
}

func (ps *ParkingSpot) GetSpotNumber() int {
	return ps.spotNumber
}

func (ps *ParkingSpot) GetVehicleType() VehicleType {
	return ps.vehicleType
}

func (ps *ParkingSpot) GetParkedVehicle() Vehicle {
	return ps.parkedVehicle
}
