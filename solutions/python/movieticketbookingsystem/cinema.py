from typing import List
from city import City
from screen import Screen

class Cinema:
    def __init__(self, cinema_id: str, name: str, city: City, screens: List[Screen]):
        self.id = cinema_id
        self.name = name
        self.city = city
        self.screens = screens

    def get_id(self) -> str:
        return self.id

    def get_name(self) -> str:
        return self.name

    def get_city(self) -> City:
        return self.city

    def get_screens(self) -> List[Screen]:
        return self.screens