package main

import "github.com/ashishps1/awesome-low-level-design/parking-lot/vehicles"

type ParkingSpot struct {
	SpotNo         int
	VehicleType    vehicles.VehicleType
	CurrentVehicle vehicles.Vehicle
}

func NewParkingSpot(vType vehicles.VehicleType, spotNo int) *ParkingSpot {
	return &ParkingSpot{SpotNo: spotNo, VehicleType: vType}
}
