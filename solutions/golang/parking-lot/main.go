package main

import (
	"fmt"
	"github.com/ashishps1/awesome-low-level-design/parking-lot/vehicles"
	"sync"
	"time"
)

func main() {
	var wg sync.WaitGroup

	parkingLots := make(map[int]*ParkingLot)

	// testing if singleton working in parking lot
	for i := 1; i <= 10; i++ {
		for j := 0; j < 5; j++ {
			wg.Add(1)
			go func(ind int) {
				parkingLots[ind] = GetInstance(ind)
				wg.Done()
			}(i)
		}
	}

	wg.Wait()
	// test if park is thread safe
	parkingLot := parkingLots[1]
	parkingLot.AddLevel(0)
	parkingLot.AddLevel(1)

	parkingLot.DisplayAvailability()

	// try to park 10 cars using different routines
	for i := 1; i <= 10; i++ {
		wg.Add(1)
		go func(ind int) {
			car := vehicles.NewCar(fmt.Sprintf("car-%d", ind))
			parkingLot.ParkVehicle(car)
			wg.Done()
		}(i)
	}
	wg.Wait()
	parkingLot.DisplayAvailability()

	//unpark any one vehicle
	ticket, _ := parkingLot.ParkVehicle(vehicles.NewTruck("truck-1"))

	time.Sleep(10 * time.Second)
	parkingLot.UnParkVehicle(ticket)
	fmt.Printf("ticket = %+v\n", ticket)

	fmt.Printf("bill for %s = %d", ticket.Vehicle.RegisNo(), ticket.TotalBill)
}
