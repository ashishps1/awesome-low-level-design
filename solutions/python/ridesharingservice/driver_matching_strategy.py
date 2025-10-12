from abc import ABC, abstractmethod
from typing import List
from driver import Driver
from location import Location
from enums import DriverStatus, RideType

class DriverMatchingStrategy(ABC):
    @abstractmethod
    def find_drivers(self, all_drivers: List[Driver], pickup_location: Location, ride_type: RideType) -> List[Driver]:
        pass

class NearestDriverMatchingStrategy(DriverMatchingStrategy):
    MAX_DISTANCE_KM = 5.0  # Max distance to consider a driver "nearby"
    
    def find_drivers(self, all_drivers: List[Driver], pickup_location: Location, ride_type: RideType) -> List[Driver]:
        print(f"Finding nearest drivers for ride type: {ride_type.value}")
        available_drivers = [
            driver for driver in all_drivers
            if (driver.get_status() == DriverStatus.ONLINE and
                driver.get_vehicle().get_type() == ride_type and
                pickup_location.distance_to(driver.get_current_location()) <= self.MAX_DISTANCE_KM)
        ]
        
        # Sort by distance
        available_drivers.sort(key=lambda d: pickup_location.distance_to(d.get_current_location()))
        return available_drivers