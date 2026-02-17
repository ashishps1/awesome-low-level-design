package concertbookingsystem

import (
	"container/heap"
	"sync"
	"time"
)

type SeatLockInfo struct {
	Seat       *Seat
	ExpiryTime time.Time
	index      int
}

type SeatLockMinHeap []*SeatLockInfo

func (h SeatLockMinHeap) Len() int { return len(h) }

func (h SeatLockMinHeap) Less(i, j int) bool { return (h)[i].ExpiryTime.Before((h)[j].ExpiryTime) }

func (h SeatLockMinHeap) Swap(i, j int) {
	(h)[i], (h)[j] = (h)[j], (h)[i]
	(h)[i].index = i
	(h)[j].index = j
}

func (h *SeatLockMinHeap) Push(x interface{}) {
	n := len(*h)
	item := x.(*SeatLockInfo)
	item.index = n
	*h = append(*h, item)
}

func (h *SeatLockMinHeap) Pop() interface{} {
	prev := *h
	n := len(prev)
	item := prev[n-1]
	item.index = -1
	*h = prev[0 : n-1]
	return item
}

type SeatLockManager struct {
	heap SeatLockMinHeap
	mu   sync.Mutex
}

func NewSeatLockManager() *SeatLockManager {
	return &SeatLockManager{
		heap: make(SeatLockMinHeap, 0),
	}
}

func (slm *SeatLockManager) AddSeatLock(seat *Seat, duration time.Duration) {
	slm.mu.Lock()
	defer slm.mu.Unlock()
	lockInfo := &SeatLockInfo{
		Seat:       seat,
		ExpiryTime: time.Now().Add(duration),
	}
	heap.Push(&slm.heap, lockInfo)
}

func (slm *SeatLockManager) ReleaseExpiredLocks() {
	slm.mu.Lock()
	defer slm.mu.Unlock()
	now := time.Now()
	for slm.heap.Len() > 0 {
		lockInfo := slm.heap[0]
		if lockInfo.ExpiryTime.After(now) {
			break
		}
		heap.Pop(&slm.heap)
		lockInfo.Seat.Release()
	}
}
