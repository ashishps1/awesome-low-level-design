package elevatorsystem

import (
	"time"
)

func Run() {
	controller := NewElevatorController(3, 5)
	defer controller.Stop()

	// Simulate elevator requests
	controller.RequestElevator(5, 10)
	controller.RequestElevator(3, 7)
	controller.RequestElevator(8, 2)
	controller.RequestElevator(1, 9)

	// Wait for elevators to process requests
	time.Sleep(30 * time.Second)
}
