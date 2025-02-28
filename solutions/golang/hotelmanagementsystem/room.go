package hotelmanagement

import (
	"fmt"
	"sync"
)

type Room struct {
	ID     string
	Type   RoomType
	Price  float64
	status RoomStatus
	mu     sync.RWMutex
}

func NewRoom(id string, roomType RoomType, price float64) *Room {
	return &Room{
		ID:     id,
		Type:   roomType,
		Price:  price,
		status: RoomStatusAvailable,
	}
}

func (r *Room) Book() error {
	r.mu.Lock()
	defer r.mu.Unlock()

	if r.status != RoomStatusAvailable {
		return fmt.Errorf("room is not available for booking")
	}
	r.status = RoomStatusBooked
	return nil
}

func (r *Room) CheckIn() error {
	r.mu.Lock()
	defer r.mu.Unlock()

	if r.status != RoomStatusBooked {
		return fmt.Errorf("room is not booked")
	}
	r.status = RoomStatusOccupied
	return nil
}

func (r *Room) CheckOut() error {
	r.mu.Lock()
	defer r.mu.Unlock()

	if r.status != RoomStatusOccupied {
		return fmt.Errorf("room is not occupied")
	}
	r.status = RoomStatusAvailable
	return nil
}

func (r *Room) GetStatus() RoomStatus {
	r.mu.RLock()
	defer r.mu.RUnlock()
	return r.status
}
