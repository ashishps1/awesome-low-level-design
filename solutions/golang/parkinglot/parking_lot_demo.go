package parkinglot

func Run() {
	parkingLot := GetParkingLotInstance()
	parkingLot.AddLevel(NewLevel(1, 100))
	parkingLot.AddLevel(NewLevel(2, 80))

	car := NewCar("ABC123")
	truck := NewTruck("XYZ789")
	motorcycle := NewMotorcycle("M1234")

	parkingLot.ParkVehicle(car)
	parkingLot.ParkVehicle(truck)
	parkingLot.ParkVehicle(motorcycle)

	parkingLot.DisplayAvailability()

	parkingLot.UnparkVehicle(motorcycle)

	parkingLot.DisplayAvailability()
}
