package observer

// FitnessDataObserver defines the interface for observers
type FitnessDataObserver interface {
	Update(steps int, calories int, distance float64)
}
