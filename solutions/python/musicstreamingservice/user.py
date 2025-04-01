class User:
    def __init__(self, user_id, username, password):
        self.id = user_id
        self.username = username
        self.password = password
        self.playlists = []

    def add_playlist(self, playlist):
        self.playlists.append(playlist)

    def remove_playlist(self, playlist):
        self.playlists.remove(playlist)

    def get_id(self):
        return self.id

    def get_username(self):
        return self.username

    def get_password(self):
        return self.password
    
    def get_playlists(self):
        return self.playlists    