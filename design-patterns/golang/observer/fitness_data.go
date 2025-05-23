package observer

// FitnessData is the concrete subject that manages observers and fitness data
type FitnessData struct {
	observers []FitnessDataObserver
	steps     int
	calories  int
	distance  float64
}

// NewFitnessData creates a new FitnessData instance
func NewFitnessData() *FitnessData {
	return &FitnessData{
		observers: make([]FitnessDataObserver, 0),
	}
}

func (f *FitnessData) RegisterObserver(observer FitnessDataObserver) {
	f.observers = append(f.observers, observer)
}

func (f *FitnessData) RemoveObserver(observer FitnessDataObserver) {
	for i, obs := range f.observers {
		if obs == observer {
			f.observers = append(f.observers[:i], f.observers[i+1:]...)
			break
		}
	}
}

func (f *FitnessData) NotifyObservers() {
	for _, observer := range f.observers {
		observer.Update(f.steps, f.calories, f.distance)
	}
}

// SetMeasurements updates the fitness data and notifies observers
func (f *FitnessData) SetMeasurements(steps int, calories int, distance float64) {
	f.steps = steps
	f.calories = calories
	f.distance = distance
	f.NotifyObservers()
}
