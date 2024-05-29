class MusicPlayer:
    def __init__(self):
        self.current_song = None
        self.is_playing = False
        self.current_time = 0

    def play_song(self, song):
        self.current_song = song
        self.is_playing = True
        self.current_time = 0
        # Start playing the song
        # ...

    def pause_song(self):
        self.is_playing = False
        # Pause the song
        # ...

    def seek_to(self, time):
        self.current_time = time
        # Seek to the specified time in the song
        # ...
