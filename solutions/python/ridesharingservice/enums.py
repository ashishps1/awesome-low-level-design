from enum import Enum

class RideType(Enum):
    SEDAN = "SEDAN"
    SUV = "SUV"
    AUTO = "AUTO"

class TripStatus(Enum):
    REQUESTED = "REQUESTED"
    ASSIGNED = "ASSIGNED"
    IN_PROGRESS = "IN_PROGRESS"
    COMPLETED = "COMPLETED"
    CANCELLED = "CANCELLED"

class DriverStatus(Enum):
    OFFLINE = "OFFLINE"
    ONLINE = "ONLINE"
    IN_TRIP = "IN_TRIP"