from enum import Enum
from typing import List

class BookingStatus(Enum):
    PENDING = 1
    CONFIRMED = 2
    CANCELLED = 3

class Booking:
    def __init__(self, booking_id: str, user, concert, seats: List['Seat']):
        self.id = booking_id
        self.user = user
        self.concert = concert
        self.seats = seats
        self.total_price = self._calculate_total_price()
        self.status = BookingStatus.PENDING

    def _calculate_total_price(self) -> float:
        return sum(seat.price for seat in self.seats)

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
            # Send booking cancellation notification to the user
            # ...