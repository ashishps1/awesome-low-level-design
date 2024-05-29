from typing import List

class Theater:
    def __init__(self, theater_id: str, name: str, location: str, shows: List):
        self._id = theater_id
        self._name = name
        self._location = location
        self._shows = shows

    @property
    def id(self) -> str:
        return self._id

    @property
    def name(self) -> str:
        return self._name

    @property
    def location(self) -> str:
        return self._location

    @property
    def shows(self) -> List:
        return self._shows
