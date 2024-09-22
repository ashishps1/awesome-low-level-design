package main

import (
	"fmt"
	"github.com/ashishps1/awesome-low-level-design/solutions/golang/parking-lot/vehicles"
)

type Level struct {
	Floor        int
	ParkingSpots map[vehicles.VehicleType]map[int]*ParkingSpot
}

// NewLevel returns a default level with 30 bike parking, 20 car parking, 10 truck parking
func NewLevel(floor int) *Level {
	parkingSpots := make(map[vehicles.VehicleType]map[int]*ParkingSpot)

	carSpots := make(map[int]*ParkingSpot)

	for spotNo := 1; spotNo <= 20; spotNo++ {
		carSpots[spotNo] = NewParkingSpot(vehicles.CAR, spotNo)
	}

	truckSpots := make(map[int]*ParkingSpot)

	for spotNo := 1; spotNo <= 10; spotNo++ {
		truckSpots[spotNo] = NewParkingSpot(vehicles.TRUCK, spotNo)
	}

	bikeSpots := make(map[int]*ParkingSpot)

	for spotNo := 1; spotNo <= 30; spotNo++ {
		bikeSpots[spotNo] = NewParkingSpot(vehicles.BIKE, spotNo)
	}

	parkingSpots[vehicles.CAR] = carSpots
	parkingSpots[vehicles.TRUCK] = truckSpots
	parkingSpots[vehicles.BIKE] = bikeSpots

	return &Level{
		Floor:        floor,
		ParkingSpots: parkingSpots,
	}
}

func (l *Level) FindParkingSpot(v vehicles.Vehicle) *ParkingSpot {
	for _, spot := range l.ParkingSpots[v.Type()] {
		if spot.CurrentVehicle == nil {
			return spot
		}
	}
	return nil
}

func (l *Level) DisplayAvailability() {
	for vtype, spotMap := range l.ParkingSpots {
		count := 0
		for _, spot := range spotMap {
			if spot.CurrentVehicle == nil {
				count++
			}
		}
		fmt.Printf("%s: %d\n", vtype.String(), count)
	}
}
