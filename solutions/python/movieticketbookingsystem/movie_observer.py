from abc import ABC, abstractmethod
from typing import List
from user import User
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from movie import Movie

class MovieObserver(ABC):
    @abstractmethod
    def update(self, movie: 'Movie') -> None:
        pass

class MovieSubject:
    def __init__(self):
        self.observers: List[MovieObserver] = []

    def add_observer(self, observer: MovieObserver) -> None:
        self.observers.append(observer)

    def remove_observer(self, observer: MovieObserver) -> None:
        if observer in self.observers:
            self.observers.remove(observer)

    def notify_observers(self) -> None:
        for observer in self.observers:
            observer.update(self)

class UserObserver(MovieObserver):
    def __init__(self, user: User):
        self.user = user

    def update(self, movie: 'Movie') -> None:
        print(f"Notification for {self.user.get_name()} ({self.user.get_id()}): Movie '{movie.get_title()}' is now available for booking!")