import threading
from vehicle import Vehicle
from vehicle_size import VehicleSize

class ParkingSpot:
    def __init__(self, spot_id: str, spot_size: VehicleSize):
        self.spot_id = spot_id
        self.spot_size = spot_size
        self.is_occupied = False
        self.parked_vehicle = None
        self._lock = threading.Lock()

    def get_spot_id(self) -> str:
        return self.spot_id

    def get_spot_size(self) -> VehicleSize:
        return self.spot_size

    def is_available(self) -> bool:
        with self._lock:
            return not self.is_occupied

    def is_occupied_spot(self) -> bool:
        return self.is_occupied

    def park_vehicle(self, vehicle: Vehicle):
        with self._lock:
            self.parked_vehicle = vehicle
            self.is_occupied = True

    def unpark_vehicle(self):
        with self._lock:
            self.parked_vehicle = None
            self.is_occupied = False

    def can_fit_vehicle(self, vehicle: Vehicle) -> bool:
        if self.is_occupied:
            return False

        if vehicle.get_size() == VehicleSize.SMALL:
            return self.spot_size == VehicleSize.SMALL
        elif vehicle.get_size() == VehicleSize.MEDIUM:
            return self.spot_size == VehicleSize.MEDIUM or self.spot_size == VehicleSize.LARGE
        elif vehicle.get_size() == VehicleSize.LARGE:
            return self.spot_size == VehicleSize.LARGE
        else:
            return False