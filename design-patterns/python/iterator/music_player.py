from .playlist import Playlist
from .iterator import Iterator

class MusicPlayer:
    def __init__(self):
        self.playlist = Playlist()

    def add_song(self, song: str) -> None:
        self.playlist.add_song(song)

    def play_all(self) -> None:
        iterator = self.playlist.create_iterator()
        print("Playing all songs:")
        while iterator.has_next():
            song = iterator.next()
            print(f"Now playing: {song}") 