import uuid
import time
from vehicle import Vehicle
from parking_spot import ParkingSpot

class ParkingTicket:
    def __init__(self, vehicle: Vehicle, spot: ParkingSpot):
        self.ticket_id = str(uuid.uuid4())
        self.vehicle = vehicle
        self.spot = spot
        self.entry_timestamp = int(time.time() * 1000)
        self.exit_timestamp = 0

    def get_ticket_id(self) -> str:
        return self.ticket_id

    def get_vehicle(self) -> Vehicle:
        return self.vehicle

    def get_spot(self) -> ParkingSpot:
        return self.spot

    def get_entry_timestamp(self) -> int:
        return self.entry_timestamp

    def get_exit_timestamp(self) -> int:
        return self.exit_timestamp

    def set_exit_timestamp(self):
        self.exit_timestamp = int(time.time() * 1000)
