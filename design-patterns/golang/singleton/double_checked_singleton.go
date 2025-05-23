package singleton

import "sync"

// DoubleCheckedSingleton implements double-checked locking singleton pattern
type DoubleCheckedSingleton struct{}

var (
	doubleCheckedInstance *DoubleCheckedSingleton
	dcMu                  sync.Mutex
)

// GetDoubleCheckedInstance returns the singleton instance
func GetDoubleCheckedInstance() *DoubleCheckedSingleton {
	if doubleCheckedInstance == nil {
		dcMu.Lock()
		defer dcMu.Unlock()

		if doubleCheckedInstance == nil {
			doubleCheckedInstance = &DoubleCheckedSingleton{}
		}
	}
	return doubleCheckedInstance
}
