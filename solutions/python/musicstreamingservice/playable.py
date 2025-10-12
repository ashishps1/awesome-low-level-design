from abc import ABC, abstractmethod
from typing import List
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from artist import Artist

class Playable(ABC):
    @abstractmethod
    def get_tracks(self) -> List['Song']:
        pass

class Song(Playable):
    def __init__(self, song_id: str, title: str, artist: 'Artist', duration_in_seconds: int):
        self._id = song_id
        self._title = title
        self._artist = artist
        self._duration_in_seconds = duration_in_seconds
    
    def get_tracks(self) -> List['Song']:
        return [self]
    
    def __str__(self) -> str:
        return f"'{self._title}' by {self._artist.get_name()}"
    
    @property
    def id(self) -> str:
        return self._id
    
    @property
    def title(self) -> str:
        return self._title
    
    @property
    def artist(self) -> 'Artist':
        return self._artist
    
class Album(Playable):
    def __init__(self, title: str):
        self._title = title
        self._tracks: List[Song] = []
    
    def add_track(self, song: Song):
        self._tracks.append(song)
    
    def get_tracks(self) -> List[Song]:
        return self._tracks.copy()
    
    def get_title(self) -> str:
        return self._title
    
class Playlist(Playable):
    def __init__(self, name: str):
        self._name = name
        self._tracks: List[Song] = []
    
    def add_track(self, song: Song):
        self._tracks.append(song)
    
    def get_tracks(self) -> List[Song]:
        return self._tracks.copy()