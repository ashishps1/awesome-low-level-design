package observer

import "fmt"

// LiveActivityDisplay displays live activity updates
type LiveActivityDisplay struct{}

func NewLiveActivityDisplay() *LiveActivityDisplay {
	return &LiveActivityDisplay{}
}

func (l *LiveActivityDisplay) Update(steps int, calories int, distance float64) {
	fmt.Printf("[LiveActivityDisplay] Steps: %d, Calories: %d, Distance: %.2f km\n", steps, calories, distance)
}
