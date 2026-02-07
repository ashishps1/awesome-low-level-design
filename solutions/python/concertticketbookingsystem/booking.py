from datetime import datetime
from typing import List
from seat import Seat
from user import User
from concert import Concert
from enums import BookingStatus, SeatStatus

class Booking:
    def __init__(self, id: str, user: User, concert: Concert, seats: List[Seat]):
        self.id = id
        self.user = user
        self.concert = concert
        self.seats = seats
        self.totalPrice = sum(seat.price for seat in self.seats)
        self.bookingStatus = BookingStatus.PENDING

    def confirmBooking(self):
        if self.bookingStatus == BookingStatus.PENDING:
            self.bookingStatus = BookingStatus.CONFIRMED
            for seat in self.seats:
                seat.confirm_booking()
            return True
    
    def cancelBooking(self):
        print(f"Booking {self.id} cancelled")
        # Release all seats
        for seat in self.seats:
            seat.release()
        self.bookingStatus = BookingStatus.CANCELLED
        return True
    
    def getId(self) -> str:
        return self.id
    
    def getUser(self) -> "User":
        return self.user
    
    def getConcert(self) -> "Concert":
        return self.concert
    
    def getSeats(self) -> List["Seat"]:
        return self.seats
    
    def getTotalPrice(self) -> float:
        return self.totalPrice
    
    def getStatus(self) -> "BookingStatus":
        return 