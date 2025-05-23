package singleton

import "sync"

// LazySingleton implements lazy initialization singleton pattern
type LazySingleton struct{}

var (
	instance *LazySingleton
	once     sync.Once
)

// GetInstance returns the singleton instance
func GetInstance() *LazySingleton {
	once.Do(func() {
		instance = &LazySingleton{}
	})
	return instance
}
