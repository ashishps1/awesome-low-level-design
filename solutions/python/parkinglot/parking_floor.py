import threading
from parking_spot import ParkingSpot
from vehicle import Vehicle
from vehicle_size import VehicleSize
from typing import Dict, Optional
from collections import defaultdict

class ParkingFloor:
    def __init__(self, floor_number: int):
        self.floor_number = floor_number
        self.spots: Dict[str, ParkingSpot] = {}
        self._lock = threading.Lock()

    def add_spot(self, spot: ParkingSpot):
        self.spots[spot.get_spot_id()] = spot

    def find_available_spot(self, vehicle: Vehicle) -> Optional[ParkingSpot]:
        with self._lock:
            available_spots = [
                spot for spot in self.spots.values()
                if not spot.is_occupied_spot() and spot.can_fit_vehicle(vehicle)
            ]
            if available_spots:
                # Sort by spot size (smallest first)
                available_spots.sort(key=lambda x: x.get_spot_size().value)
                return available_spots[0]
            return None

    def display_availability(self):
        print(f"--- Floor {self.floor_number} Availability ---")
        available_counts = defaultdict(int)
        
        for spot in self.spots.values():
            if not spot.is_occupied_spot():
                available_counts[spot.get_spot_size()] += 1

        for size in VehicleSize:
            print(f"  {size.value} spots: {available_counts[size]}")