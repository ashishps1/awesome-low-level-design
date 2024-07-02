from ride_service import RideService
from passenger import Passenger
from location import Location
from driver import Driver, DriverStatus

class RideSharingServiceDemo:
    def run():
        ride_service = RideService()

        # Create passengers
        passenger1 = Passenger(1, "John Doe", "1234567890", Location(37.7749, -122.4194))
        passenger2 = Passenger(2, "Jane Smith", "9876543210", Location(37.7860, -122.4070))
        ride_service.add_passenger(passenger1)
        ride_service.add_passenger(passenger2)

        # Create drivers
        driver1 = Driver(1, "Alice Johnson", "4567890123", "ABC123", Location(37.7749, -122.4194), DriverStatus.AVAILABLE)
        driver2 = Driver(2, "Bob Williams", "7890123456", "XYZ789", Location(37.7860, -122.4070), DriverStatus.AVAILABLE)
        ride_service.add_driver(driver1)
        ride_service.add_driver(driver2)

        # Passenger 1 requests a ride
        ride_service.request_ride(passenger1, passenger1.get_location(), Location(37.7887, -122.4098))

        # Driver 1 accepts the ride
        ride = ride_service.get_requested_rides().pop(0)
        ride_service.accept_ride(driver1, ride)

        # Start the ride
        ride_service.start_ride(ride)

        # Complete the ride
        ride_service.complete_ride(ride)

        # Passenger 2 requests a ride
        ride_service.request_ride(passenger2, passenger2.get_location(), Location(37.7749, -122.4194))

        # Driver 2 accepts the ride
        ride2 = ride_service.get_requested_rides().pop(0)
        ride_service.accept_ride(driver2, ride2)

        # Passenger 2 cancels the ride
        ride_service.cancel_ride(ride2)

if __name__ == "__main__":
    RideSharingServiceDemo.run()