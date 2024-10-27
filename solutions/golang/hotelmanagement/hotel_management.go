package hotelmanagement

import (
	"fmt"
	"sync"
	"time"
)

type HotelManagementSystem struct {
	guests       map[string]*Guest
	rooms        map[string]*Room
	reservations map[string]*Reservation
	mu           sync.RWMutex
}

var (
	instance *HotelManagementSystem
	once     sync.Once
)

func GetHotelManagementSystem() *HotelManagementSystem {
	once.Do(func() {
		instance = &HotelManagementSystem{
			guests:       make(map[string]*Guest),
			rooms:        make(map[string]*Room),
			reservations: make(map[string]*Reservation),
		}
	})
	return instance
}

func (h *HotelManagementSystem) AddGuest(guest *Guest) {
	h.mu.Lock()
	defer h.mu.Unlock()
	h.guests[guest.ID] = guest
}

func (h *HotelManagementSystem) GetGuest(guestID string) *Guest {
	h.mu.RLock()
	defer h.mu.RUnlock()
	return h.guests[guestID]
}

func (h *HotelManagementSystem) AddRoom(room *Room) {
	h.mu.Lock()
	defer h.mu.Unlock()
	h.rooms[room.ID] = room
}

func (h *HotelManagementSystem) GetRoom(roomID string) *Room {
	h.mu.RLock()
	defer h.mu.RUnlock()
	return h.rooms[roomID]
}

func (h *HotelManagementSystem) BookRoom(guest *Guest, room *Room, checkInDate, checkOutDate time.Time) (*Reservation, error) {
	h.mu.Lock()
	defer h.mu.Unlock()

	if room.GetStatus() != RoomStatusAvailable {
		return nil, fmt.Errorf("room is not available")
	}

	if err := room.Book(); err != nil {
		return nil, err
	}

	reservationID := fmt.Sprintf("RES%d", time.Now().UnixNano())
	reservation := NewReservation(reservationID, guest, room, checkInDate, checkOutDate)
	h.reservations[reservationID] = reservation

	return reservation, nil
}

func (h *HotelManagementSystem) CancelReservation(reservationID string) error {
	h.mu.Lock()
	defer h.mu.Unlock()

	reservation, exists := h.reservations[reservationID]
	if !exists {
		return fmt.Errorf("reservation not found")
	}

	if err := reservation.Cancel(); err != nil {
		return err
	}

	delete(h.reservations, reservationID)
	return nil
}

func (h *HotelManagementSystem) CheckIn(reservationID string) error {
	h.mu.Lock()
	defer h.mu.Unlock()

	reservation, exists := h.reservations[reservationID]
	if !exists {
		return fmt.Errorf("reservation not found")
	}

	if reservation.Status != ReservationStatusConfirmed {
		return fmt.Errorf("invalid reservation status")
	}

	return reservation.Room.CheckIn()
}

func (h *HotelManagementSystem) CheckOut(reservationID string, payment Payment) error {
	h.mu.Lock()
	defer h.mu.Unlock()

	reservation, exists := h.reservations[reservationID]
	if !exists {
		return fmt.Errorf("reservation not found")
	}

	if reservation.Status != ReservationStatusConfirmed {
		return fmt.Errorf("invalid reservation status")
	}

	days := reservation.CheckOutDate.Sub(reservation.CheckInDate).Hours() / 24
	amount := reservation.Room.Price * days

	if !payment.ProcessPayment(amount) {
		return fmt.Errorf("payment failed")
	}

	if err := reservation.Room.CheckOut(); err != nil {
		return err
	}

	delete(h.reservations, reservationID)
	return nil
}
