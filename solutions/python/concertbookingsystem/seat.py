from enum import Enum

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
    def __init__(self, seat_id: str, seat_number: str, seat_type: SeatType, price: float):
        self.id = seat_id
        self.seat_number = seat_number
        self.seat_type = seat_type
        self.price = price
        self.status = SeatStatus.AVAILABLE

    def book(self):
        if self.status == SeatStatus.AVAILABLE:
            self.status = SeatStatus.BOOKED
        else:
            raise SeatNotAvailableException("Seat is already booked or reserved.")

    def release(self):
        if self.status == SeatStatus.BOOKED:
            self.status = SeatStatus.AVAILABLE