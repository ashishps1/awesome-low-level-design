package parkinglot

type Level struct {
	floor        int
	parkingSpots []*ParkingSpot
}

func NewLevel(floor int, numSpots int) *Level {
	level := &Level{floor: floor}
	bikeSpots := int(float64(numSpots) * 0.50)
	carSpots := int(float64(numSpots) * 0.40)

	for i := 1; i <= bikeSpots; i++ {
		level.parkingSpots = append(level.parkingSpots, NewParkingSpot(i, MOTORCYCLE))
	}
	for i := bikeSpots + 1; i <= bikeSpots+carSpots; i++ {
		level.parkingSpots = append(level.parkingSpots, NewParkingSpot(i, CAR))
	}
	for i := bikeSpots + carSpots + 1; i <= numSpots; i++ {
		level.parkingSpots = append(level.parkingSpots, NewParkingSpot(i, TRUCK))
	}
	return level
}

func (l *Level) ParkVehicle(vehicle Vehicle) bool {
	for _, spot := range l.parkingSpots {
		if spot.IsAvailable() && spot.GetVehicleType() == vehicle.GetType() {
			spot.ParkVehicle(vehicle)
			return true
		}
	}
	return false
}

func (l *Level) UnparkVehicle(vehicle Vehicle) bool {
	for _, spot := range l.parkingSpots {
		if !spot.IsAvailable() && spot.GetParkedVehicle() == vehicle {
			spot.UnparkVehicle()
			return true
		}
	}
	return false
}

func (l *Level) DisplayAvailability() {
	for _, spot := range l.parkingSpots {
		status := "Available"
		if !spot.IsAvailable() {
			status = "Occupied"
		}
		println("Level:", l.floor, "Spot:", spot.GetSpotNumber(), "Status:", status, "Type:", spot.GetVehicleType())
	}
}
