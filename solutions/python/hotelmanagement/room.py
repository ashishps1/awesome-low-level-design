from threading import Lock
from room_status import RoomStatus
from room_type import RoomType

class Room:
    def __init__(self, id: str, type: RoomType, price: float):
        self.id = id
        self.type = type
        self.price = price
        self.status = RoomStatus.AVAILABLE
        self.lock = Lock()

    def book(self):
        with self.lock:
            if self.status == RoomStatus.AVAILABLE:
                self.status = RoomStatus.BOOKED
            else:
                raise ValueError("Room is not available for booking.")

    def check_in(self):
        with self.lock:
            if self.status == RoomStatus.BOOKED:
                self.status = RoomStatus.OCCUPIED
            else:
                raise ValueError("Room is not booked.")

    def check_out(self):
        with self.lock:
            if self.status == RoomStatus.OCCUPIED:
                self.status = RoomStatus.AVAILABLE
            else:
                raise ValueError("Room is not occupied.")
