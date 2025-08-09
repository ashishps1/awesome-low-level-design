from abc import ABC, abstractmethod
from typing import List
from seat import Seat

class PricingStrategy(ABC):
    @abstractmethod
    def calculate_price(self, seats: List[Seat]) -> float:
        pass

class WeekdayPricingStrategy(PricingStrategy):
    def calculate_price(self, seats: List[Seat]) -> float:
        return sum(seat.get_type().get_price() for seat in seats)

class WeekendPricingStrategy(PricingStrategy):
    WEEKEND_SURCHARGE = 1.2  # 20% surcharge

    def calculate_price(self, seats: List[Seat]) -> float:
        base_price = sum(seat.get_type().get_price() for seat in seats)
        return base_price * self.WEEKEND_SURCHARGE