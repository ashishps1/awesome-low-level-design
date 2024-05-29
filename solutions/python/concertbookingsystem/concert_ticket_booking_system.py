from typing import List
import uuid
import datetime
from concert import Concert
from booking import Booking
from seat import Seat, SeatStatus
from user import User

class ConcertTicketBookingSystem:
    _instance = None
    _lock = object()

    def __new__(cls):
        if not cls._instance:
            with cls._lock:
                if not cls._instance:
                    cls._instance = super().__new__(cls)
        return cls._instance

    def __init__(self):
        self.concerts = {}
        self.bookings = {}

    def add_concert(self, concert: Concert):
        self.concerts[concert.id] = concert

    def get_concert(self, concert_id: str) -> Concert:
        return self.concerts.get(concert_id)

    def search_concerts(self, artist: str, venue: str, date_time: datetime) -> List[Concert]:
        return [concert for concert in self.concerts.values()
                if concert.artist.lower() == artist.lower() and
                concert.venue.lower() == venue.lower() and
                concert.date_time == date_time]

    def book_tickets(self, user: User, concert: Concert, seats: List[Seat]) -> Booking:
        with self._lock:
            # Check seat availability and book seats
            for seat in seats:
                if seat.status != SeatStatus.AVAILABLE:
                    raise SeatNotAvailableException(f"Seat {seat.seat_number} is not available.")
            for seat in seats:
                seat.book()

            # Create booking
            booking_id = self._generate_booking_id()
            booking = Booking(booking_id, user, concert, seats)
            self.bookings[booking_id] = booking

            # Process payment
            self._process_payment(booking)

            # Confirm booking
            booking.confirm_booking()

            return booking

    def cancel_booking(self, booking_id: str):
        booking = self.bookings.get(booking_id)
        if booking:
            booking.cancel_booking()
            del self.bookings[booking_id]

    def _process_payment(self, booking: Booking):
        # Process payment for the booking
        # ...
        pass

    def _generate_booking_id(self) -> str:
        return "BKG" + str(uuid.uuid4())