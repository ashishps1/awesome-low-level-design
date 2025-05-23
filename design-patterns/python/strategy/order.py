class Order:
    """Order data class containing order details"""
    
    def __init__(self, weight: float, distance: float, value: float):
        self._weight = weight  # in kg
        self._distance = distance  # in km
        self._value = value  # in currency units
    
    @property
    def weight(self) -> float:
        return self._weight
    
    @property
    def distance(self) -> float:
        return self._distance
    
    @property
    def value(self) -> float:
        return self._value
    
    def __str__(self) -> str:
        return f"Order(weight={self._weight}kg, distance={self._distance}km, value=${self._value})"