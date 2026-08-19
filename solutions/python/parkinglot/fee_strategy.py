from abc import ABC, abstractmethod
from parking_ticket import ParkingTicket
from vehicle_size import VehicleSize
import math

class FeeStrategy(ABC):
    @abstractmethod
    def get_hourly_rate(self, parking_ticket: ParkingTicket) -> float:
        pass

    def calculate_fee(self, parking_ticket: ParkingTicket) -> float:
        duration = parking_ticket.get_exit_timestamp() - parking_ticket.get_entry_timestamp()
        hours = max(1, math.ceil(duration / (1000 * 60 * 60)))
        return hours * self.get_hourly_rate(parking_ticket)

class FlatRateFeeStrategy(FeeStrategy):
    RATE_PER_HOUR = 10.0

    def get_hourly_rate(self, parking_ticket: ParkingTicket) -> float:
        return self.RATE_PER_HOUR

class VehicleBasedFeeStrategy(FeeStrategy):
    HOURLY_RATES = {
        VehicleSize.SMALL: 10.0,
        VehicleSize.MEDIUM: 20.0,
        VehicleSize.LARGE: 30.0,
    }

    def get_hourly_rate(self, parking_ticket: ParkingTicket) -> float:
        return self.HOURLY_RATES[parking_ticket.get_vehicle().get_size()]
