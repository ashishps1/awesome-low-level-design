from datetime import datetime
from typing import List, Dict
from collections import defaultdict
import itertools
from movie import Movie
from theater import Theater
from show import Show
from booking import Booking, BookingStatus
from seat import Seat, SeatStatus
from user import User

class MovieTicketBookingSystem:
    _instance = None

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
            cls._instance.movies = []
            cls._instance.theaters = []
            cls._instance.shows = {}
            cls._instance.bookings = {}
            cls._instance.booking_counter = itertools.count(1)
        return cls._instance

    @staticmethod
    def get_instance():
        if MovieTicketBookingSystem._instance is None:
            MovieTicketBookingSystem()
        return MovieTicketBookingSystem._instance

    def add_movie(self, movie: Movie):
        self.movies.append(movie)

    def add_theater(self, theater: Theater):
        self.theaters.append(theater)

    def add_show(self, show: Show):
        self.shows[show.id] = show

    def get_movies(self) -> List[Movie]:
        return self.movies

    def get_theaters(self) -> List[Theater]:
        return self.theaters

    def get_show(self, show_id: str) -> Show:
        return self.shows.get(show_id)

    def book_tickets(self, user: User, show: Show, selected_seats: List[Seat]) -> Booking:
        if self._are_seats_available(show, selected_seats):
            self._mark_seats_as_booked(show, selected_seats)
            total_price = self._calculate_total_price(selected_seats)
            booking_id = self._generate_booking_id()
            booking = Booking(booking_id, user, show, selected_seats, total_price, BookingStatus.PENDING)
            self.bookings[booking_id] = booking
            return booking
        return None

    def _are_seats_available(self, show: Show, selected_seats: List[Seat]) -> bool:
        for seat in selected_seats:
            show_seat = show.seats.get(seat.id)
            if show_seat is None or show_seat.status != SeatStatus.AVAILABLE:
                return False
        return True

    def _mark_seats_as_booked(self, show: Show, selected_seats: List[Seat]):
        for seat in selected_seats:
            show_seat = show.seats.get(seat.id)
            show_seat.status = SeatStatus.BOOKED

    def _calculate_total_price(self, selected_seats: List[Seat]) -> float:
        return sum(seat.price for seat in selected_seats)

    def _generate_booking_id(self) -> str:
        booking_number = next(self._instance.booking_counter)
        timestamp = datetime.now().strftime("%Y%m%d%H%M%S")
        return f"BKG{timestamp}{booking_number:06d}"

    def confirm_booking(self, booking_id: str):
        booking = self.bookings.get(booking_id)
        if booking and booking.status == BookingStatus.PENDING:
            booking.status = BookingStatus.CONFIRMED
            # Process payment and send confirmation
            # ...

    def cancel_booking(self, booking_id: str):
        booking = self.bookings.get(booking_id)
        if booking and booking.status != BookingStatus.CANCELLED:
            booking.status = BookingStatus.CANCELLED
            self._mark_seats_as_available(booking.show, booking.seats)
            # Process refund and send cancellation notification
            # ...

    def _mark_seats_as_available(self, show: Show, seats: List[Seat]):
        for seat in seats:
            show_seat = show.seats.get(seat.id)
            show_seat.status = SeatStatus.AVAILABLE
