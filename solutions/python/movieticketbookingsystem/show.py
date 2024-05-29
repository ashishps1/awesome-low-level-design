from datetime import datetime
from typing import Dict
from movie import Movie
from theater import Theater
from seat import Seat

class Show:
    def __init__(self, show_id: str, movie: Movie, theater: Theater, start_time: datetime, end_time: datetime, seats: Dict[str, Seat]):
        self._id = show_id
        self._movie = movie
        self._theater = theater
        self._start_time = start_time
        self._end_time = end_time
        self._seats = seats

    @property
    def id(self) -> str:
        return self._id

    @property
    def movie(self) -> Movie:
        return self._movie

    @property
    def theater(self) -> Theater:
        return self._theater

    @property
    def start_time(self) -> datetime:
        return self._start_time

    @property
    def end_time(self) -> datetime:
        return self._end_time

    @property
    def seats(self) -> Dict[str, Seat]:
        return self._seats
