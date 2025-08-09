from abc import ABC
from vehicle_size import VehicleSize

class Vehicle(ABC):
    def __init__(self, license_number: str, size: VehicleSize):
        self.license_number = license_number
        self.size = size

    def get_license_number(self) -> str:
        return self.license_number

    def get_size(self) -> VehicleSize:
        return self.size