from datetime import datetime
from movie import Movie
from screen import Screen
from pricing_strategy import PricingStrategy

class Show:
    def __init__(self, show_id: str, movie: Movie, screen: Screen, start_time: datetime, pricing_strategy: PricingStrategy):
        self.id = show_id
        self.movie = movie
        self.screen = screen
        self.start_time = start_time
        self.pricing_strategy = pricing_strategy

    def get_id(self) -> str:
        return self.id

    def get_movie(self) -> Movie:
        return self.movie

    def get_screen(self) -> Screen:
        return self.screen

    def get_start_time(self) -> datetime:
        return self.start_time

    def get_pricing_strategy(self) -> PricingStrategy:
        return self.pricing_strategy