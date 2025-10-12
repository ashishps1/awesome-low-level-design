import math

class Address:
    def __init__(self, street: str, city: str, zip_code: str, latitude: float, longitude: float):
        self.street = street
        self.city = city
        self.zip_code = zip_code
        self.latitude = latitude
        self.longitude = longitude

    def get_city(self) -> str:
        return self.city

    def distance_to(self, other: 'Address') -> float:
        lat_diff = self.latitude - other.latitude
        lon_diff = self.longitude - other.longitude
        return math.sqrt(lat_diff * lat_diff + lon_diff * lon_diff)

    def __str__(self) -> str:
        return f"{self.street}, {self.city}, {self.zip_code} @({self.latitude}, {self.longitude})" 