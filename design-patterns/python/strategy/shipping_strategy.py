from abc import ABC, abstractmethod


class ShippingStrategy(ABC):
    """Strategy interface for shipping cost calculation"""
    
    @abstractmethod
    def calculate_cost(self, order) -> float:
        pass