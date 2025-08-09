from vehicle import Vehicle
from location import Location
from enums import DriverStatus, TripStatus
from trip import Trip
from typing import TYPE_CHECKING
from user import User

if TYPE_CHECKING:
    from trip import Trip

class Driver(User):
    def __init__(self, name: str, contact: str, vehicle: Vehicle, initial_location: Location):
        super().__init__(name, contact)
        self._vehicle = vehicle
        self._current_location = initial_location
        self._status = DriverStatus.OFFLINE  # Default status
    
    def get_vehicle(self) -> Vehicle:
        return self._vehicle
    
    def get_status(self) -> DriverStatus:
        return self._status
    
    def set_status(self, status: DriverStatus):
        self._status = status
        print(f"Driver {self.get_name()} is now {status.value}")
    
    def get_current_location(self) -> Location:
        return self._current_location
    
    def set_current_location(self, current_location: Location):
        self._current_location = current_location
    
    def on_update(self, trip: 'Trip'):
        print(f"--- Notification for Driver {self.get_name()} ---")
        print(f"  Trip {trip.get_id()} status: {trip.get_status().value}.")
        if trip.get_status() == TripStatus.REQUESTED:
            print("  A new ride is available for you to accept.")
        print("--------------------------------\n")