import math

class Location:
    def __init__(self, latitude: float, longitude: float):
        self._latitude = latitude
        self._longitude = longitude
    
    def distance_to(self, other: 'Location') -> float:
        dx = self._latitude - other._latitude
        dy = self._longitude - other._longitude
        return math.sqrt(dx * dx + dy * dy)  # Euclidean for simplicity
    
    def __str__(self) -> str:
        return f"Location({self._latitude}, {self._longitude})"