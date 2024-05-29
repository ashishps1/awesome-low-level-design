class Song:
    def __init__(self, song_id, title, artist, album, duration):
        self.id = song_id
        self.title = title
        self.artist = artist
        self.album = album
        self.duration = duration

    def get_id(self):
        return self.id

    def get_title(self):
        return self.title

    def get_artist(self):
        return self.artist

    def get_album(self):
        return self.album