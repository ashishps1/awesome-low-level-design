from .iterator import Iterator
from .playlist import Playlist

class PlaylistIterator(Iterator[str]):
    def __init__(self, playlist: Playlist):
        self.playlist = playlist
        self.index = 0

    def has_next(self) -> bool:
        return self.index < self.playlist.get_size()

    def next(self) -> str:
        song = self.playlist.get_song_at(self.index)
        self.index += 1
        return song 