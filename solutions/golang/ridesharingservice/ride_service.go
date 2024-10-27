package ridesharingservice

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

type RideService struct {
	passengers     map[int]*Passenger
	drivers        map[int]*Driver
	rides          map[int]*Ride
	requestedRides chan *Ride
	mu             sync.Mutex
}

var instance *RideService
var once sync.Once

func GetRideService() *RideService {
	once.Do(func() {
		instance = &RideService{
			passengers:     make(map[int]*Passenger),
			drivers:        make(map[int]*Driver),
			rides:          make(map[int]*Ride),
			requestedRides: make(chan *Ride, 10),
		}
	})
	return instance
}

func (rs *RideService) AddPassenger(passenger *Passenger) {
	rs.mu.Lock()
	defer rs.mu.Unlock()
	rs.passengers[passenger.ID] = passenger
}

func (rs *RideService) AddDriver(driver *Driver) {
	rs.mu.Lock()
	defer rs.mu.Unlock()
	rs.drivers[driver.ID] = driver
}

func (rs *RideService) RequestRide(passenger *Passenger, source, destination *Location) {
	ride := &Ride{
		ID:          rs.generateRideID(),
		Passenger:   passenger,
		Source:      source,
		Destination: destination,
		Status:      Requested,
	}
	rs.requestedRides <- ride
	rs.notifyDrivers(ride)
}

func (rs *RideService) AcceptRide(driver *Driver, ride *Ride) {
	rs.mu.Lock()
	defer rs.mu.Unlock()
	if ride.Status == Requested {
		ride.Driver = driver
		ride.Status = Accepted
		driver.Status = Busy
		rs.notifyPassenger(ride)
	}
}

func (rs *RideService) StartRide(ride *Ride) {
	rs.mu.Lock()
	defer rs.mu.Unlock()
	if ride.Status == Accepted {
		ride.Status = InProgress
		rs.notifyPassenger(ride)
	}
}

func (rs *RideService) CompleteRide(ride *Ride) {
	rs.mu.Lock()
	defer rs.mu.Unlock()
	if ride.Status == InProgress {
		ride.Status = Completed
		ride.Driver.Status = Available
		ride.Fare = rs.calculateFare(ride)
		rs.notifyPassenger(ride)
		rs.notifyDriver(ride)
	}
}

func (rs *RideService) CancelRide(ride *Ride) {
	rs.mu.Lock()
	defer rs.mu.Unlock()
	if ride.Status == Requested || ride.Status == Accepted {
		ride.Status = Cancelled
		if ride.Driver != nil {
			ride.Driver.Status = Available
		}
		rs.notifyPassenger(ride)
		rs.notifyDriver(ride)
	}
}

func (rs *RideService) notifyDrivers(ride *Ride) {
	for _, driver := range rs.drivers {
		if driver.Status == Available && rs.calculateDistance(driver.Location, ride.Source) <= 5.0 {
			fmt.Printf("Notifying driver %s about ride request: %d\n", driver.Name, ride.ID)
		}
	}
}

func (rs *RideService) notifyPassenger(ride *Ride) {
	message := ""
	switch ride.Status {
	case Accepted:
		message = fmt.Sprintf("Your ride has been accepted by driver: %s", ride.Driver.Name)
	case InProgress:
		message = "Your ride is in progress"
	case Completed:
		message = fmt.Sprintf("Your ride has been completed. Fare: $%.2f", ride.Fare)
	case Cancelled:
		message = "Your ride has been cancelled"
	}
	fmt.Printf("Notifying passenger %s: %s\n", ride.Passenger.Name, message)
}

func (rs *RideService) notifyDriver(ride *Ride) {
	if ride.Driver != nil {
		message := ""
		switch ride.Status {
		case Completed:
			message = fmt.Sprintf("Ride completed. Fare: $%.2f", ride.Fare)
		case Cancelled:
			message = "Ride cancelled by passenger"
		}
		fmt.Printf("Notifying driver %s: %s\n", ride.Driver.Name, message)
	}
}

func (rs *RideService) calculateFare(ride *Ride) float64 {
	baseFare := 2.0
	perKmFare := 1.5
	perMinuteFare := 0.25

	distance := rs.calculateDistance(ride.Source, ride.Destination)
	duration := rs.calculateDuration(ride.Source, ride.Destination)

	return baseFare + (distance * perKmFare) + (duration * perMinuteFare)
}

func (rs *RideService) calculateDistance(source, destination *Location) float64 {
	return rand.Float64()*20 + 1
}

func (rs *RideService) calculateDuration(source, destination *Location) float64 {
	distance := rs.calculateDistance(source, destination)
	return (distance / 30) * 60
}

func (rs *RideService) generateRideID() int {
	return int(time.Now().Unix())
}
