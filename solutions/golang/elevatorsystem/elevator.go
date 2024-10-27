package elevatorsystem

import (
	"fmt"
	"sync"
	"time"
)

type Elevator struct {
	id               int
	capacity         int
	currentFloor     int
	currentDirection Direction
	requests         chan *Request
	stopChan         chan struct{}
	mu               sync.RWMutex
}

func NewElevator(id, capacity int) *Elevator {
	return &Elevator{
		id:               id,
		capacity:         capacity,
		currentFloor:     1,
		currentDirection: DirectionUp,
		requests:         make(chan *Request, capacity),
		stopChan:         make(chan struct{}),
	}
}

func (e *Elevator) AddRequest(request *Request) bool {
	select {
	case e.requests <- request:
		fmt.Printf("Elevator %d added request: Floor %d to %d\n",
			e.id, request.SourceFloor, request.DestinationFloor)
		return true
	default:
		return false
	}
}

func (e *Elevator) getCurrentFloor() int {
	e.mu.RLock()
	defer e.mu.RUnlock()
	return e.currentFloor
}

func (e *Elevator) setCurrentFloor(floor int) {
	e.mu.Lock()
	defer e.mu.Unlock()
	e.currentFloor = floor
}

func (e *Elevator) Run() {
	go func() {
		for {
			select {
			case request := <-e.requests:
				e.processRequest(request)
			case <-e.stopChan:
				return
			}
		}
	}()
}

func (e *Elevator) Stop() {
	close(e.stopChan)
}

func (e *Elevator) processRequest(request *Request) {
	startFloor := e.getCurrentFloor()
	endFloor := request.DestinationFloor

	if startFloor < endFloor {
		e.currentDirection = DirectionUp
		for i := startFloor; i <= endFloor; i++ {
			e.setCurrentFloor(i)
			fmt.Printf("Elevator %d reached floor %d\n", e.id, i)
			time.Sleep(time.Second) // Simulating elevator movement
		}
	} else if startFloor > endFloor {
		e.currentDirection = DirectionDown
		for i := startFloor; i >= endFloor; i-- {
			e.setCurrentFloor(i)
			fmt.Printf("Elevator %d reached floor %d\n", e.id, i)
			time.Sleep(time.Second) // Simulating elevator movement
		}
	}
}
