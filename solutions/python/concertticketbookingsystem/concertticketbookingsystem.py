from datetime import datetime
from threading import Lock
from typing import List
from concert import Concert
from user import User
from seat import Seat, SeatNotAvailableException
from booking import Booking
from enums import SeatStatus
import uuid
class ConcertTicketBookingSystem:
    _instance = None

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
            cls._instance.concerts = {}
            cls._instance.bookings = {}
            cls._instance._lock = Lock()
        return cls._instance
    
    def addConcert(self, concert: Concert):
        self.concerts[concert.id] = concert

    def getConcert(self, concertId: str) -> "Concert":
        if concertId in self.concerts:
            return self.concerts[concertId]
        print(f"No concert with concertId {concertId} found")
    
    def searchConcerts(self, artist: str, venue: str, dateTime: datetime) -> List["Concert"]:
        return [ concert for _, concert in self.concerts.items() \
            if concert.getArtist() == artist \
            and concert.getVenue() == venue \
            and concert.getDateTime() == dateTime ]
    
    def bookTickets(self, user: User, concert: Concert, seats: List["Seat"]) -> "Booking":
        with self._lock:
            # ensure all the seats are available
            for seat in seats:
                if seat.seatStatus != SeatStatus.AVAILABLE:
                    raise SeatNotAvailableException("Seat not available")
            for seat in seats:
                # Reserve all seats
                seat.book()
            
            bookingId = self._generateId(user, concert)
            booking = Booking(bookingId, user, concert, seats)

            self.bookings[bookingId] = booking
            self._processPayment(booking)
            booking.confirmBooking()
            print(f"Booking {bookingId} confirmed")
            return booking
    
    def cancelBooking(self, bookingId: str):
        with self._lock:
            if bookingId in self.bookings:
                booking = self.bookings.pop(bookingId)
                booking.cancelBooking()

    def _processPayment(self, booking: Booking) -> bool:
        price = booking.getTotalPrice()
        print(f"Processed payment for amount {price}")
        return True
    
    def _generateId(self, user: User, concert: Concert) -> str:
        return f"BKG{user.id}-{concert.id}-{uuid.uuid4()}"