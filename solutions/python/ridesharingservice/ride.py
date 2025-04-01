from enum import Enum

class RideStatus(Enum):
    REQUESTED = 1
    ACCEPTED = 2
    IN_PROGRESS = 3
    COMPLETED = 4
    CANCELLED = 5

class Ride:
    def __init__(self, id, passenger, driver, source, destination, status, fare):
        self.id = id
        self.passenger = passenger
        self.driver = driver
        self.source = source
        self.destination = destination
        self.status = status
        self.fare = fare

    def set_driver(self, driver):
        self.driver = driver

    def set_status(self, status):
        self.status = status

    def set_fare(self, fare):
        self.fare = fare

    def get_id(self):
        return self.id

    def get_passenger(self):
        return self.passenger

    def get_driver(self):
        return self.driver

    def get_source(self):
        return self.source

    def get_destination(self):
        return self.destination

    def get_status(self):
        return self.status

    def get_fare(self):
        return self.fare