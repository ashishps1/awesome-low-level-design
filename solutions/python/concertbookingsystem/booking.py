from enum import Enum
from typing import List
from user import User
from concert import Concert
from seat import Seat

class BookingStatus(Enum):
    PENDING = 1
    CONFIRMED = 2
    CANCELLED = 3

class Booking:
    def __init__(self, id: str, user: User, concert: Concert, seats: List[Seat]):
        self.id = id
        self.user = user
        self.concert = concert
        self.seats = seats
        self.total_price = sum(seat.price for seat in seats)
        self.status = BookingStatus.PENDING

    def confirm_booking(self):
        if self.status == BookingStatus.PENDING:
            self.status = BookingStatus.CONFIRMED
            # Send booking confirmation to the user
            # ...

    def cancel_booking(self):
        if self.status == BookingStatus.CONFIRMED:
            self.status = BookingStatus.CANCELLED
            for seat in self.seats:
                seat.release()
            print(f"Booking {self.id} cancelled")
            # Send booking cancellation notification to the user
            # ...