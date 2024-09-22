package main

import (
	"github.com/ashishps1/awesome-low-level-design/solutions/golang/parking-lot/vehicles"
	"time"
)

type Ticket struct {
	EntryTime   time.Time
	ExitTime    time.Time
	ParkingSpot *ParkingSpot
	Vehicle     vehicles.Vehicle
	TotalBill   int
}

func NewTicket(spot *ParkingSpot, vehicle vehicles.Vehicle) *Ticket {
	return &Ticket{
		EntryTime:   time.Now(),
		ExitTime:    time.Time{},
		ParkingSpot: spot,
		Vehicle:     vehicle,
		TotalBill:   0,
	}
}

func (t *Ticket) CalculateAmount() {
	t.ExitTime = time.Now()
	timeSpent := int(t.ExitTime.Sub(t.EntryTime).Seconds())
	t.TotalBill = timeSpent * t.Vehicle.Cost()
}
