from abc import ABC, abstractmethod
from typing import List
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from artist import Artist
    from playable import Album

class ArtistObserver(ABC):
    @abstractmethod
    def update(self, artist: 'Artist', new_album: 'Album'):
        pass

class Subject:
    def __init__(self):
        self._observers: List[ArtistObserver] = []
    
    def add_observer(self, observer: ArtistObserver):
        self._observers.append(observer)
    
    def remove_observer(self, observer: ArtistObserver):
        if observer in self._observers:
            self._observers.remove(observer)
    
    def notify_observers(self, artist: 'Artist', album: 'Album'):
        for observer in self._observers:
            observer.update(artist, album)