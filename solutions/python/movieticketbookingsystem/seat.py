from seat_type import SeatType
from seat_status import SeatStatus

class Seat:
    def __init__(self, seat_id: str, row: int, column: int, seat_type: SeatType, price: float, status: SeatStatus):
        self._id = seat_id
        self._row = row
        self._column = column
        self._type = seat_type
        self._price = price
        self._status = status

    @property
    def id(self) -> str:
        return self._id

    @property
    def row(self) -> int:
        return self._row

    @property
    def column(self) -> int:
        return self._column

    @property
    def type(self) -> SeatType:
        return self._type

    @property
    def price(self) -> float:
        return self._price

    @property
    def status(self) -> SeatStatus:
        return self._status

    @status.setter
    def status(self, status: SeatStatus):
        self._status = status
