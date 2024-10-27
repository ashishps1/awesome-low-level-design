package stackoverflow

import (
	"sync"
	"time"
)

var (
	idCounter int
	idMutex   sync.Mutex
)

func generateID() int {
	idMutex.Lock()
	defer idMutex.Unlock()

	// Simple time-based ID generator with an incremental counter
	idCounter++
	return int(time.Now().UnixNano()/int64(time.Millisecond)) + idCounter
}
