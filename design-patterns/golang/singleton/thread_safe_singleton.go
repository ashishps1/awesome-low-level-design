package singleton

import "sync"

// ThreadSafeSingleton implements thread-safe singleton pattern
type ThreadSafeSingleton struct{}

var (
	threadSafeInstance *ThreadSafeSingleton
	mu                 sync.Mutex
)

// GetThreadSafeInstance returns the singleton instance
func GetThreadSafeInstance() *ThreadSafeSingleton {
	mu.Lock()
	defer mu.Unlock()

	if threadSafeInstance == nil {
		threadSafeInstance = &ThreadSafeSingleton{}
	}
	return threadSafeInstance
}
