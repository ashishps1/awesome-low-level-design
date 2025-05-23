package observer

import "fmt"

// GoalNotifier notifies when a goal is reached
type GoalNotifier struct {
	goalSteps int
}

func NewGoalNotifier(goalSteps int) *GoalNotifier {
	return &GoalNotifier{goalSteps: goalSteps}
}

func (g *GoalNotifier) Update(steps int, calories int, distance float64) {
	if steps >= g.goalSteps {
		fmt.Printf("[GoalNotifier] Congratulations! Goal of %d steps reached!\n", g.goalSteps)
	} else {
		fmt.Printf("[GoalNotifier] %d steps to go to reach your goal of %d steps.\n", g.goalSteps-steps, g.goalSteps)
	}
} 