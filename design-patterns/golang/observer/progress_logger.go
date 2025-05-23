package observer

import "fmt"

// ProgressLogger logs progress updates
type ProgressLogger struct{}

func NewProgressLogger() *ProgressLogger {
	return &ProgressLogger{}
}

func (p *ProgressLogger) Update(steps int, calories int, distance float64) {
	fmt.Printf("[ProgressLogger] Progress logged: %d steps, %d calories, %.2f km\n", steps, calories, distance)
}
