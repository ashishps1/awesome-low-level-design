package airlinemanagementsystem

import (
    "sync"
    "time"
)

type AirlineManagementSystem struct {
    flights         []*Flight
    aircrafts       []*Aircraft
    flightSearch    *FlightSearch
    bookingManager  *BookingManager
    paymentProcessor *PaymentProcessor
    mu              sync.RWMutex
}

func NewAirlineManagementSystem() *AirlineManagementSystem {
    system := &AirlineManagementSystem{
        flights:          make([]*Flight, 0),
        aircrafts:        make([]*Aircraft, 0),
        bookingManager:   GetBookingManager(),
        paymentProcessor: GetPaymentProcessor(),
    }
    system.flightSearch = NewFlightSearch(system.flights)
    return system
}

func (ams *AirlineManagementSystem) AddFlight(flight *Flight) {
    ams.mu.Lock()
    defer ams.mu.Unlock()
    ams.flights = append(ams.flights, flight)
}

func (ams *AirlineManagementSystem) AddAircraft(aircraft *Aircraft) {
    ams.mu.Lock()
    defer ams.mu.Unlock()
    ams.aircrafts = append(ams.aircrafts, aircraft)
}

func (ams *AirlineManagementSystem) SearchFlights(source, destination string, date time.Time) []*Flight {
    return ams.flightSearch.SearchFlights(source, destination, date)
}

func (ams *AirlineManagementSystem) BookFlight(flight *Flight, passenger *Passenger, seat *Seat, price float64) *Booking {
    return ams.bookingManager.CreateBooking(flight, passenger, seat, price)
}

func (ams *AirlineManagementSystem) CancelBooking(bookingNumber string) {
    ams.bookingManager.CancelBooking(bookingNumber)
}

func (ams *AirlineManagementSystem) ProcessPayment(payment *Payment) {
    ams.paymentProcessor.ProcessPayment(payment)
}