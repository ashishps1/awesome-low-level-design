import threading
from typing import Dict, Optional
from driver import Driver
from driver_matching_strategy import DriverMatchingStrategy
from enums import DriverStatus, RideType
from pricing_strategy import PricingStrategy
from rider import Rider
from trip import Trip
from location import Location
from vehicle import Vehicle

class RideSharingService:
    _instance = None
    _lock = threading.Lock()
    
    def __new__(cls):
        if cls._instance is None:
            with cls._lock:
                if cls._instance is None:
                    cls._instance = super().__new__(cls)
                    cls._instance._initialized = False
        return cls._instance
    
    def __init__(self):
        if not self._initialized:
            self._riders: Dict[str, Rider] = {}
            self._drivers: Dict[str, Driver] = {}
            self._trips: Dict[str, Trip] = {}
            self._pricing_strategy: Optional[PricingStrategy] = None
            self._driver_matching_strategy: Optional[DriverMatchingStrategy] = None
            self._initialized = True
    
    @classmethod
    def get_instance(cls):
        return cls()
    
    # Allow changing strategies at runtime for extensibility
    def set_pricing_strategy(self, pricing_strategy: PricingStrategy):
        self._pricing_strategy = pricing_strategy
    
    def set_driver_matching_strategy(self, driver_matching_strategy: DriverMatchingStrategy):
        self._driver_matching_strategy = driver_matching_strategy
    
    def register_rider(self, name: str, contact: str) -> Rider:
        rider = Rider(name, contact)
        self._riders[rider.get_id()] = rider
        return rider
    
    def register_driver(self, name: str, contact: str, vehicle: Vehicle, initial_location: Location) -> Driver:
        driver = Driver(name, contact, vehicle, initial_location)
        self._drivers[driver.get_id()] = driver
        return driver
    
    def request_ride(self, rider_id: str, pickup: Location, dropoff: Location, ride_type: RideType) -> Optional[Trip]:
        rider = self._riders.get(rider_id)
        if rider is None:
            raise KeyError("Rider not found")
        
        print(f"\n--- New Ride Request from {rider.get_name()} ---")
        
        # 1. Find available drivers
        available_drivers = self._driver_matching_strategy.find_drivers(
            list(self._drivers.values()), pickup, ride_type
        )
        
        if not available_drivers:
            print("No drivers available for your request. Please try again later.")
            return None
        
        print(f"Found {len(available_drivers)} available driver(s).")
        
        # 2. Calculate fare
        fare = self._pricing_strategy.calculate_fare(pickup, dropoff, ride_type)
        print(f"Estimated fare: ${fare:.2f}")
        
        # 3. Create a trip using the Builder
        trip = Trip.TripBuilder() \
            .with_rider(rider) \
            .with_pickup_location(pickup) \
            .with_dropoff_location(dropoff) \
            .with_fare(fare) \
            .build()
        
        self._trips[trip.get_id()] = trip
        
        # 4. Notify nearby drivers (in a real system, this would be a push notification)
        print("Notifying nearby drivers of the new ride request...")
        for driver in available_drivers:
            print(f" > Notifying {driver.get_name()} at {driver.get_current_location()}")
            driver.on_update(trip)
        
        return trip
    
    def accept_ride(self, driver_id: str, trip_id: str):
        driver = self._drivers.get(driver_id)
        trip = self._trips.get(trip_id)
        if driver is None or trip is None:
            raise KeyError("Driver or Trip not found")
        
        print(f"\n--- Driver {driver.get_name()} accepted the ride ---")
        
        driver.set_status(DriverStatus.IN_TRIP)
        trip.assign_driver(driver)
    
    def start_trip(self, trip_id: str):
        trip = self._trips.get(trip_id)
        if trip is None:
            raise KeyError("Trip not found")
        print(f"\n--- Trip {trip.get_id()} is starting ---")
        trip.start_trip()
    
    def end_trip(self, trip_id: str):
        trip = self._trips.get(trip_id)
        if trip is None:
            raise KeyError("Trip not found")
        print(f"\n--- Trip {trip.get_id()} is ending ---")
        trip.end_trip()
        
        # Update statuses and history
        driver = trip.get_driver()
        driver.set_status(DriverStatus.ONLINE)  # Driver is available again
        driver.set_current_location(trip.get_dropoff_location())  # Update driver location
        
        rider = trip.get_rider()
        driver.add_trip_to_history(trip)
        rider.add_trip_to_history(trip)
        
        print(f"Driver {driver.get_name()} is now back online at {driver.get_current_location()}")