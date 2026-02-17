from datetime import datetime
from typing import List
from seat import Seat
from dataclasses import dataclass

@dataclass
class Concert:
    id: str
    artist: str
    venue: str
    dateTime: datetime
    seats: List[Seat]

    def getId(self) -> str:
        return self.id
    
    def getArtist(self) -> str:
        return self.artist
    
    def getVenue(self) -> str:
        return self.venue
    
    def getDateTime(self) -> datetime:
        return self.dateTime
    
    def getSeats(self) -> List["Seat"]:
        return self.seats