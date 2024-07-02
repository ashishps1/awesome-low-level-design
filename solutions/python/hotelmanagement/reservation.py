from datetime import datetime
from guest import Guest
from room import Room
from reservation_status import ReservationStatus

class Reservation:
    def __init__(self, reservation_id: str, guest: Guest, room: Room, check_in_date: datetime, check_out_date: datetime):
        self._id = reservation_id
        self._guest = guest
        self._room = room
        self._check_in_date = check_in_date
        self._check_out_date = check_out_date
        self._status = ReservationStatus.CONFIRMED

    @property
    def id(self) -> str:
        return self._id

    @property
    def guest(self) -> Guest:
        return self._guest

    @property
    def room(self) -> Room:
        return self._room

    @property
    def check_in_date(self) -> datetime:
        return self._check_in_date

    @property
    def check_out_date(self) -> datetime:
        return self._check_out_date

    @property
    def status(self) -> ReservationStatus:
        return self._status

    @status.setter
    def status(self, status: ReservationStatus):
        self._status = status

    def cancel(self):
        if self._status == ReservationStatus.CONFIRMED:
            self._status = ReservationStatus.CANCELLED
            self._room.check_out()
        else:
            raise Exception("Reservation is not confirmed.")
