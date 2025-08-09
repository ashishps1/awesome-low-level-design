from typing import List
from seat import Seat

class Screen:
    def __init__(self, screen_id: str):
        self.id = screen_id
        self.seats: List[Seat] = []

    def add_seat(self, seat: Seat) -> None:
        self.seats.append(seat)

    def get_id(self) -> str:
        return self.id

    def get_seats(self) -> List[Seat]:
        return self.seats