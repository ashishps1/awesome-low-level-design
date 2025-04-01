class Playlist:
    def __init__(self, playlist_id, name, owner):
        self.id = playlist_id
        self.name = name
        self.owner = owner
        self.songs = []

    def add_song(self, song):
        self.songs.append(song)

    def remove_song(self, song):
        self.songs.remove(song)

    def get_songs(self):
        return self.songs