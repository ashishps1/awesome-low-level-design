from typing import List
from show import Show
from user import User
from seat import Seat
from booking_status import BookingStatus

class Booking:
    def __init__(self, booking_id: str, user: User, show: Show, seats: List[Seat], total_price: float, status: BookingStatus):
        self._id = booking_id
        self._user = user
        self._show = show
        self._seats = seats
        self._total_price = total_price
        self._status = status

    @property
    def id(self) -> str:
        return self._id

    @property
    def user(self) -> User:
        return self._user

    @property
    def show(self) -> Show:
        return self._show

    @property
    def seats(self) -> List[Seat]:
        return self._seats

    @property
    def total_price(self) -> float:
        return self._total_price

    @property
    def status(self) -> BookingStatus:
        return self._status

    @status.setter
    def status(self, status: BookingStatus):
        self._status = status
