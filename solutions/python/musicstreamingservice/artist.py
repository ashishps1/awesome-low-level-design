class Artist:
    def __init__(self, artist_id, name, albums):
        self.id = artist_id
        self.name = name
        self.albums = albums

    def get_id(self):
        return self.id

    def get_albums(self):
        return self.albums