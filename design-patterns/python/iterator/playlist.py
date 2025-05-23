from typing import List
from .iterable_collection import IterableCollection
from .iterator import Iterator
from .playlist_iterator import PlaylistIterator

class Playlist(IterableCollection[str]):
    def __init__(self):
        self.songs: List[str] = []

    def add_song(self, song: str) -> None:
        self.songs.append(song)

    def get_song_at(self, index: int) -> str:
        return self.songs[index]

    def get_size(self) -> int:
        return len(self.songs)

    def create_iterator(self) -> Iterator[str]:
        return PlaylistIterator(self) 