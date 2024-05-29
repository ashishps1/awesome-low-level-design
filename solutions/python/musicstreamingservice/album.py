class Album:
    def __init__(self, album_id, title, artist, songs):
        self.id = album_id
        self.title = title
        self.artist = artist
        self.songs = songs

    def get_id(self):
        return self.id

    def get_title(self):
        return self.title

    def get_artist(self):
        return self.artist

    def get_songs(self):
        return self.songs