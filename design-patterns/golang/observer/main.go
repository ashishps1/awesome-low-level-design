package observer

func main() {
	fitnessData := NewFitnessData()

	liveDisplay := NewLiveActivityDisplay()
	logger := NewProgressLogger()
	goalNotifier := NewGoalNotifier(10000)

	fitnessData.RegisterObserver(liveDisplay)
	fitnessData.RegisterObserver(logger)
	fitnessData.RegisterObserver(goalNotifier)

	fitnessData.SetMeasurements(3000, 120, 2.5)
	fitnessData.SetMeasurements(7000, 250, 5.0)
	fitnessData.SetMeasurements(10000, 400, 8.0)

	fitnessData.RemoveObserver(logger)
	fitnessData.SetMeasurements(12000, 500, 10.0)
} 