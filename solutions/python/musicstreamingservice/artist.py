from playable import Album
from typing import List
from observer import Subject

class Artist(Subject):
    def __init__(self, artist_id: str, name: str):
        super().__init__()
        self._id = artist_id
        self._name = name
        self._discography: List['Album'] = []
    
    def release_album(self, album: 'Album'):
        self._discography.append(album)
        print(f"[System] Artist {self._name} has released a new album: {album.get_title()}")
        self.notify_observers(self, album)
    
    @property
    def id(self) -> str:
        return self._id
    
    def get_name(self) -> str:
        return self._name