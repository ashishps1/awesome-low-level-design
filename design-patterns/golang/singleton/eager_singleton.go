package singleton

// EagerSingleton implements eager initialization singleton pattern
type EagerSingleton struct{}

// The single instance, created immediately
var instance = &EagerSingleton{}

// GetInstance returns the singleton instance
func GetInstance() *EagerSingleton {
	return instance
}
