package trafficsignalsystem

import (
	"sync"
	"time"
)

type TrafficController struct {
	roads map[string]*Road
	mu    sync.Mutex
}

var instance *TrafficController
var once sync.Once

// GetTrafficController returns the singleton instance of TrafficController
func GetTrafficController() *TrafficController {
	once.Do(func() {
		instance = &TrafficController{roads: make(map[string]*Road)}
	})
	return instance
}

func (tc *TrafficController) AddRoad(road *Road) {
	tc.mu.Lock()
	defer tc.mu.Unlock()
	tc.roads[road.ID] = road
}

func (tc *TrafficController) StartTrafficControl() {
	tc.mu.Lock()
	defer tc.mu.Unlock()

	for _, road := range tc.roads {
		trafficLight := road.TrafficLight
		go func(tl *TrafficLight) {
			for {
				time.Sleep(time.Duration(tl.RedDuration) * time.Millisecond)
				tl.ChangeSignal(Green)
				time.Sleep(time.Duration(tl.GreenDuration) * time.Millisecond)
				tl.ChangeSignal(Yellow)
				time.Sleep(time.Duration(tl.YellowDuration) * time.Millisecond)
				tl.ChangeSignal(Red)
			}
		}(trafficLight)
	}
}

func (tc *TrafficController) HandleEmergency(roadID string) {
	tc.mu.Lock()
	defer tc.mu.Unlock()

	if road, exists := tc.roads[roadID]; exists {
		trafficLight := road.TrafficLight
		trafficLight.ChangeSignal(Green)
		// Emergency handling logic here
	}
}
