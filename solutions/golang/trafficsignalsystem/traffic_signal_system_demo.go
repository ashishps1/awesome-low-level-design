package trafficsignalsystem

import "time"

// Run demonstrates the Traffic Signal System functionality
func Run() {
	// Initialize the traffic controller
	trafficController := GetTrafficController()

	// Create roads
	road1 := NewRoad("R1", "Main Street")
	road2 := NewRoad("R2", "Broadway")
	road3 := NewRoad("R3", "Park Avenue")
	road4 := NewRoad("R4", "Elm Street")

	// Create traffic lights
	trafficLight1 := NewTrafficLight("TL1", 6000, 3000, 9000)
	trafficLight2 := NewTrafficLight("TL2", 6000, 3000, 9000)
	trafficLight3 := NewTrafficLight("TL3", 6000, 3000, 9000)
	trafficLight4 := NewTrafficLight("TL4", 6000, 3000, 9000)

	// Assign traffic lights to roads
	road1.SetTrafficLight(trafficLight1)
	road2.SetTrafficLight(trafficLight2)
	road3.SetTrafficLight(trafficLight3)
	road4.SetTrafficLight(trafficLight4)

	// Add roads to the traffic controller
	trafficController.AddRoad(road1)
	trafficController.AddRoad(road2)
	trafficController.AddRoad(road3)
	trafficController.AddRoad(road4)

	// Start traffic control
	go trafficController.StartTrafficControl()

	// Simulate an emergency after some time
	time.Sleep(10 * time.Second)
	trafficController.HandleEmergency("R2")
}
