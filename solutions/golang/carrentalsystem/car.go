package carrentalsystem

import "sync"

type Car struct {
	Make              string
	Model             string
	Year              int
	LicensePlate      string
	RentalPricePerDay float64
	available         bool
	mu                sync.Mutex
}

func NewCar(make, model string, year int, licensePlate string, rentalPricePerDay float64) *Car {
	return &Car{
		Make:              make,
		Model:             model,
		Year:              year,
		LicensePlate:      licensePlate,
		RentalPricePerDay: rentalPricePerDay,
		available:         true,
	}
}

func (c *Car) IsAvailable() bool {
	c.mu.Lock()
	defer c.mu.Unlock()
	return c.available
}

func (c *Car) SetAvailable(available bool) {
	c.mu.Lock()
	defer c.mu.Unlock()
	c.available = available
}
