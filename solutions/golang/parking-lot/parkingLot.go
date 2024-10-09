package main

import (
	"errors"
	"fmt"
	"github.com/ashishps1/awesome-low-level-design/solutions/golang/parking-lot/vehicles"
	"sync"
)

var (
	singletonMap map[int]*ParkingLot
	once         sync.Once
	instanceLock sync.Mutex
	parkLock     sync.Mutex
)

type ParkingLot struct {
	Name    string
	Address string // this could be another struct but keeping it simple for now
	Levels  []*Level
}

func GetInstance(id int) *ParkingLot {
	once.Do(func() {
		singletonMap = make(map[int]*ParkingLot)
	})
	if _, isPresent := singletonMap[id]; !isPresent {
		instanceLock.Lock()
		if _, isPresent = singletonMap[id]; !isPresent {
			fmt.Printf("Creating new parking lot for id: %d\n", id)
			pLot := ParkingLot{}
			singletonMap[id] = &pLot
		}
		instanceLock.Unlock()
	}
	return singletonMap[id]
}

func (p *ParkingLot) ParkVehicle(vehicle vehicles.Vehicle) (*Ticket, error) {
	// Find the best spot available
	parkLock.Lock()
	defer parkLock.Unlock()

	fmt.Printf("Parking vehicle no: %s\n", vehicle.RegisNo())
	var spot *ParkingSpot
	for _, level := range p.Levels {
		if spot = level.FindParkingSpot(vehicle); spot != nil {
			break
		} else {
			return nil, errors.New("parking full")
		}
	}
	// Mark spot as occupied
	spot.CurrentVehicle = vehicle
	// Generate ticket and return
	ticket := NewTicket(spot, vehicle)

	return ticket, nil
}

func (p *ParkingLot) DisplayAvailability() {
	fmt.Println("Following no of spots available:")
	for floor, level := range p.Levels {
		fmt.Printf("level %d:\n", floor)
		level.DisplayAvailability()
		fmt.Println()
	}
	fmt.Println()
}

func (p *ParkingLot) UnParkVehicle(ticket *Ticket) {
	// empty the spot
	ticket.ParkingSpot.CurrentVehicle = nil
	// calculate the amount
	ticket.CalculateAmount()
}

func (p *ParkingLot) AddLevel(floor int) {
	p.Levels = append(p.Levels, NewLevel(floor))
}
