from room_status import RoomStatus
from room_type import RoomType

class Room:
    def __init__(self, room_id: str, room_type: RoomType, price: float):
        self._id = room_id
        self._type = room_type
        self._price = price
        self._status = RoomStatus.AVAILABLE

    @property
    def id(self) -> str:
        return self._id

    @property
    def type(self) -> RoomType:
        return self._type

    @property
    def price(self) -> float:
        return self._price

    @property
    def status(self) -> RoomStatus:
        return self._status

    def book(self):
        if self._status == RoomStatus.AVAILABLE:
            self._status = RoomStatus.BOOKED
        else:
            raise Exception("Room is not available for booking.")

    def check_in(self):
        if self._status == RoomStatus.BOOKED:
            self._status = RoomStatus.OCCUPIED
        else:
            raise Exception("Room is not booked.")

    def check_out(self):
        if self._status == RoomStatus.OCCUPIED:
            self._status = RoomStatus.AVAILABLE
        else:
            raise Exception("Room is not occupied.")
