from enum import Enum
from threading import Lock

class SeatType(Enum):
    REGULAR = 1
    PREMIUM = 2
    VIP = 3

class SeatStatus(Enum):
    AVAILABLE = 1
    BOOKED = 2
    RESERVED = 3

class SeatNotAvailableException(Exception):
    pass

class Seat:
    def __init__(self, id: str, seat_number: str, seat_type: SeatType, price: float):
        self.id = id
        self.seat_number = seat_number
        self.seat_type = seat_type
        self.price = price
        self.status = SeatStatus.AVAILABLE
        self._lock = Lock()

    def book(self):
        with self._lock:
            if self.status == SeatStatus.AVAILABLE:
                self.status = SeatStatus.BOOKED
            else:
                raise SeatNotAvailableException("Seat is already booked or reserved.")

    def release(self):
        with self._lock:
            if self.status == SeatStatus.BOOKED:
                self.status = SeatStatus.AVAILABLE