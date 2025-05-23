package observer

// FitnessDataSubject defines the interface for the subject
type FitnessDataSubject interface {
	RegisterObserver(observer FitnessDataObserver)
	RemoveObserver(observer FitnessDataObserver)
	NotifyObservers()
}
