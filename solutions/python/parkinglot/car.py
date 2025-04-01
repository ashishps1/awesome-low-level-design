from vehicle_type import VehicleType
from vehicle import Vehicle

class Car(Vehicle):
    def __init__(self, license_plate: str):
        super().__init__(license_plate, VehicleType.CAR)