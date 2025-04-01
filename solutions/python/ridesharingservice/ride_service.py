from concurrent.futures import ThreadPoolExecutor
from ride import Ride, RideStatus
from driver import DriverStatus
import random
import math
import time

class RideService:
    _instance = None
    _lock = ThreadPoolExecutor(max_workers=1)

    def __new__(cls):
        if not cls._instance:
            with cls._lock:
                if not cls._instance:
                    cls._instance = super().__new__(cls)
                    cls._instance._initialize()
        return cls._instance

    def _initialize(self):
        self.passengers = {}
        self.drivers = {}
        self.rides = {}
        self.requested_rides = []

    def add_passenger(self, passenger):
        self.passengers[passenger.get_id()] = passenger

    def add_driver(self, driver):
        self.drivers[driver.get_id()] = driver

    def request_ride(self, passenger, source, destination):
        ride_id = self._generate_ride_id()
        ride = Ride(ride_id, passenger, None, source, destination, RideStatus.REQUESTED, 0.0)
        self.requested_rides.append(ride)
        self._notify_drivers(ride)

    def accept_ride(self, driver, ride):
        if ride.get_status() == RideStatus.REQUESTED:
            ride.set_driver(driver)
            ride.set_status(RideStatus.ACCEPTED)
            driver.set_status(DriverStatus.BUSY)
            self._notify_passenger(ride)

    def start_ride(self, ride):
        if ride.get_status() == RideStatus.ACCEPTED:
            ride.set_status(RideStatus.IN_PROGRESS)
            self._notify_passenger(ride)

    def complete_ride(self, ride):
        if ride.get_status() == RideStatus.IN_PROGRESS:
            ride.set_status(RideStatus.COMPLETED)
            ride.get_driver().set_status(DriverStatus.AVAILABLE)
            fare = self._calculate_fare(ride)
            ride.set_fare(fare)
            self._process_payment(ride, fare)
            self._notify_passenger(ride)
            self._notify_driver(ride)

    def cancel_ride(self, ride):
        if ride.get_status() in [RideStatus.REQUESTED, RideStatus.ACCEPTED]:
            ride.set_status(RideStatus.CANCELLED)
            if ride.get_driver():
                ride.get_driver().set_status(DriverStatus.AVAILABLE)
            self._notify_passenger(ride)
            self._notify_driver(ride)

    def _notify_drivers(self, ride):
        for driver in self.drivers.values():
            if driver.get_status() == DriverStatus.AVAILABLE:
                distance = self._calculate_distance(driver.get_location(), ride.get_source())
                if distance <= 5.0:  # Notify drivers within 5 km radius
                    # Send notification to the driver
                    print(f"Notifying driver: {driver.get_name()} about ride request: {ride.get_id()}")

    def _notify_passenger(self, ride):
        passenger = ride.get_passenger()
        message = ""
        if ride.get_status() == RideStatus.ACCEPTED:
            message = f"Your ride has been accepted by driver: {ride.get_driver().get_name()}"
        elif ride.get_status() == RideStatus.IN_PROGRESS:
            message = "Your ride is in progress"
        elif ride.get_status() == RideStatus.COMPLETED:
            message = f"Your ride has been completed. Fare: ${ride.get_fare():.2f}"
        elif ride.get_status() == RideStatus.CANCELLED:
            message = "Your ride has been cancelled"
        # Send notification to the passenger
        print(f"Notifying passenger: {passenger.get_name()} - {message}")

    def _notify_driver(self, ride):
        driver = ride.get_driver()
        if driver:
            message = ""
            if ride.get_status() == RideStatus.COMPLETED:
                message = f"Ride completed. Fare: ${ride.get_fare():.2f}"
            elif ride.get_status() == RideStatus.CANCELLED:
                message = "Ride cancelled by passenger"
            # Send notification to the driver
            print(f"Notifying driver: {driver.get_name()} - {message}")

    def _calculate_fare(self, ride):
        base_fare = 2.0
        per_km_fare = 1.5
        per_minute_fare = 0.25

        distance = self._calculate_distance(ride.get_source(), ride.get_destination())
        duration = self._calculate_duration(ride.get_source(), ride.get_destination())

        fare = base_fare + (distance * per_km_fare) + (duration * per_minute_fare)
        return round(fare, 2)

    def _calculate_distance(self, source, destination):
        # Calculate the distance between two locations using a distance formula (e.g., Haversine formula)
        # For simplicity, let's assume a random distance between 1 and 20 km
        return random.uniform(1, 20)

    def _calculate_duration(self, source, destination):
        # Calculate the estimated duration between two locations based on distance and average speed
        # For simplicity, let's assume an average speed of 30 km/h
        distance = self._calculate_distance(source, destination)
        return (distance / 30) * 60  # Convert hours to minutes

    def _process_payment(self, ride, amount):
        # Process the payment for the ride
        pass

    def _generate_ride_id(self):
        return int(time.time())

    def get_rides(self):
        return self.rides

    def get_requested_rides(self):
        return self.requested_rides