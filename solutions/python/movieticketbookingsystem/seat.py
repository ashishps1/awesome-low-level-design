from enums import SeatStatus, SeatType

class Seat:
    def __init__(self, seat_id: str, row: int, col: int, seat_type: SeatType):
        self.id = seat_id
        self.row = row
        self.col = col
        self.type = seat_type
        self.status = SeatStatus.AVAILABLE

    def get_id(self) -> str:
        return self.id

    def get_row(self) -> int:
        return self.row

    def get_col(self) -> int:
        return self.col

    def get_type(self) -> SeatType:
        return self.type

    def get_status(self) -> SeatStatus:
        return self.status

    def set_status(self, status: SeatStatus) -> None:
        self.status = status