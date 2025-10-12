from abc import ABC, abstractmethod
from location import Location
from enums import RideType

class PricingStrategy(ABC):
    @abstractmethod
    def calculate_fare(self, pickup: Location, dropoff: Location, ride_type: RideType) -> float:
        pass

class FlatRatePricingStrategy(PricingStrategy):
    BASE_FARE = 5.0
    FLAT_RATE = 1.5
    
    def calculate_fare(self, pickup: Location, dropoff: Location, ride_type: RideType) -> float:
        distance = pickup.distance_to(dropoff)
        return self.BASE_FARE + distance * self.FLAT_RATE

class VehicleBasedPricingStrategy(PricingStrategy):
    BASE_FARE = 2.50
    RATE_PER_KM = {
        RideType.SEDAN: 1.50,
        RideType.SUV: 2.00,
        RideType.AUTO: 1.00
    }
    
    def calculate_fare(self, pickup: Location, dropoff: Location, ride_type: RideType) -> float:
        return self.BASE_FARE + self.RATE_PER_KM[ride_type] * pickup.distance_to(dropoff)