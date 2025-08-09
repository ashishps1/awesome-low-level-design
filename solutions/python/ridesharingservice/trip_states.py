from abc import ABC, abstractmethod
from enums import TripStatus
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from driver import Driver
    from trip import Trip

class TripState(ABC):
    @abstractmethod
    def request(self, trip: 'Trip'):
        pass
    
    @abstractmethod
    def assign(self, trip: 'Trip', driver: 'Driver'):
        pass
    
    @abstractmethod
    def start(self, trip: 'Trip'):
        pass
    
    @abstractmethod
    def end(self, trip: 'Trip'):
        pass

class RequestedState(TripState):
    def request(self, trip: 'Trip'):
        print("Trip is already in requested state.")
    
    def assign(self, trip: 'Trip', driver: 'Driver'):
        trip.set_driver(driver)
        trip.set_status(TripStatus.ASSIGNED)
        trip.set_state(AssignedState())
    
    def start(self, trip: 'Trip'):
        print("Cannot start a trip that has not been assigned a driver.")
    
    def end(self, trip: 'Trip'):
        print("Cannot end a trip that has not been assigned a driver.")

class AssignedState(TripState):
    def request(self, trip: 'Trip'):
        print("Trip has already been requested and assigned.")
    
    def assign(self, trip: 'Trip', driver: 'Driver'):
        print("Trip is already assigned. To re-assign, cancel first.")
    
    def start(self, trip: 'Trip'):
        trip.set_status(TripStatus.IN_PROGRESS)
        trip.set_state(InProgressState())
    
    def end(self, trip: 'Trip'):
        print("Cannot end a trip that has not started.")


class InProgressState(TripState):
    def request(self, trip: 'Trip'):
        print("Trip is already in progress.")
    
    def assign(self, trip: 'Trip', driver: 'Driver'):
        print("Cannot assign a new driver while trip is in progress.")
    
    def start(self, trip: 'Trip'):
        print("Trip is already in progress.")
    
    def end(self, trip: 'Trip'):
        trip.set_status(TripStatus.COMPLETED)
        trip.set_state(CompletedState())


class CompletedState(TripState):
    def request(self, trip: 'Trip'):
        print("Cannot request a trip that is already completed.")
    
    def assign(self, trip: 'Trip', driver: 'Driver'):
        print("Cannot assign a driver to a completed trip.")
    
    def start(self, trip: 'Trip'):
        print("Cannot start a completed trip.")
    
    def end(self, trip: 'Trip'):
        print("Trip is already completed.")