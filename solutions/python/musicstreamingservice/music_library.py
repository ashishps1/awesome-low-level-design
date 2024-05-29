class MusicLibrary:
    _instance = None

    def __init__(self):
        self.songs = {}
        self.albums = {}
        self.artists = {}

    @classmethod
    def get_instance(cls):
        if cls._instance is None:
            cls._instance = cls()
        return cls._instance

    def add_song(self, song):
        self.songs[song.get_id()] = song

    def add_album(self, album):
        self.albums[album.get_id()] = album
        for song in album.get_songs():
            self.add_song(song)

    def add_artist(self, artist):
        self.artists[artist.get_id()] = artist
        for album in artist.get_albums():
            self.add_album(album)

    def get_song(self, song_id):
        return self.songs.get(song_id)

    def get_album(self, album_id):
        return self.albums.get(album_id)

    def get_artist(self, artist_id):
        return self.artists.get(artist_id)

    def search_songs(self, query):
        matching_songs = []
        for song in self.songs.values():
            if query in song.get_title() or query in song.get_artist() or query in song.get_album():
                matching_songs.append(song)
        return matching_songs