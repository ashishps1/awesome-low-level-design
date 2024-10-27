package elevatorsystem

import (
	"math"
	"sync"
)

type ElevatorController struct {
	elevators []*Elevator
	mu        sync.RWMutex
}

func NewElevatorController(numElevators, capacity int) *ElevatorController {
	controller := &ElevatorController{
		elevators: make([]*Elevator, numElevators),
	}

	for i := 0; i < numElevators; i++ {
		elevator := NewElevator(i+1, capacity)
		controller.elevators[i] = elevator
		elevator.Run()
	}

	return controller
}

func (ec *ElevatorController) RequestElevator(sourceFloor, destinationFloor int) {
	elevator := ec.findOptimalElevator(sourceFloor, destinationFloor)
	request := NewRequest(sourceFloor, destinationFloor)
	elevator.AddRequest(request)
}

func (ec *ElevatorController) findOptimalElevator(sourceFloor, destinationFloor int) *Elevator {
	ec.mu.RLock()
	defer ec.mu.RUnlock()

	var optimalElevator *Elevator
	minDistance := math.MaxInt32

	for _, elevator := range ec.elevators {
		distance := int(math.Abs(float64(sourceFloor - elevator.getCurrentFloor())))
		if distance < minDistance {
			minDistance = distance
			optimalElevator = elevator
		}
	}

	return optimalElevator
}

func (ec *ElevatorController) Stop() {
	ec.mu.Lock()
	defer ec.mu.Unlock()

	for _, elevator := range ec.elevators {
		elevator.Stop()
	}
}
