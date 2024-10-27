package carrentalsystem

import (
	"crypto/rand"
	"encoding/hex"
	"fmt"
	"strings"
	"sync"
	"time"
)

type RentalSystem struct {
	cars         map[string]*Car
	reservations map[string]*Reservation
	processor    PaymentProcessor
	mu           sync.RWMutex
}

var (
	instance *RentalSystem
	once     sync.Once
)

func GetRentalSystem() *RentalSystem {
	once.Do(func() {
		instance = &RentalSystem{
			cars:         make(map[string]*Car),
			reservations: make(map[string]*Reservation),
			processor:    NewCreditCardPaymentProcessor(),
		}
	})
	return instance
}

func (rs *RentalSystem) AddCar(car *Car) {
	rs.mu.Lock()
	defer rs.mu.Unlock()
	rs.cars[car.LicensePlate] = car
}

func (rs *RentalSystem) RemoveCar(licensePlate string) {
	rs.mu.Lock()
	defer rs.mu.Unlock()
	delete(rs.cars, licensePlate)
}

func (rs *RentalSystem) SearchCars(make, model string, startDate, endDate time.Time) []*Car {
	rs.mu.RLock()
	defer rs.mu.RUnlock()

	var availableCars []*Car
	for _, car := range rs.cars {
		if strings.EqualFold(car.Make, make) &&
			strings.EqualFold(car.Model, model) &&
			car.IsAvailable() &&
			rs.isCarAvailable(car, startDate, endDate) {
			availableCars = append(availableCars, car)
		}
	}
	return availableCars
}

func (rs *RentalSystem) isCarAvailable(car *Car, startDate, endDate time.Time) bool {
	for _, reservation := range rs.reservations {
		if reservation.Car == car {
			if !startDate.After(reservation.EndDate) && !endDate.Before(reservation.StartDate) {
				return false
			}
		}
	}
	return true
}

func (rs *RentalSystem) MakeReservation(customer *Customer, car *Car, startDate, endDate time.Time) (*Reservation, error) {
	rs.mu.Lock()
	defer rs.mu.Unlock()

	if !rs.isCarAvailable(car, startDate, endDate) {
		return nil, fmt.Errorf("car is not available for the selected dates")
	}

	reservationID := rs.generateReservationID()
	reservation := NewReservation(reservationID, customer, car, startDate, endDate)
	rs.reservations[reservationID] = reservation
	car.SetAvailable(false)

	return reservation, nil
}

func (rs *RentalSystem) CancelReservation(reservationID string) {
	rs.mu.Lock()
	defer rs.mu.Unlock()

	if reservation, exists := rs.reservations[reservationID]; exists {
		reservation.Car.SetAvailable(true)
		delete(rs.reservations, reservationID)
	}
}

func (rs *RentalSystem) ProcessPayment(reservation *Reservation) bool {
	return rs.processor.ProcessPayment(reservation.TotalPrice)
}

func (rs *RentalSystem) generateReservationID() string {
	bytes := make([]byte, 4)
	rand.Read(bytes)
	return fmt.Sprintf("RES%s", hex.EncodeToString(bytes))
}
