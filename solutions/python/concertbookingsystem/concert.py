from datetime import datetime
from typing import List

class Concert:
    def __init__(self, concert_id: str, artist: str, venue: str, date_time: datetime, seats: List['Seat']):
        self.id = concert_id
        self.artist = artist
        self.venue = venue
        self.date_time = date_time
        self.seats = seats