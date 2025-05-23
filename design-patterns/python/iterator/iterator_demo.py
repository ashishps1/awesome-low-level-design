from .music_player import MusicPlayer

def main():
    # Create a music player
    player = MusicPlayer()

    # Add some songs to the playlist
    player.add_song("Bohemian Rhapsody - Queen")
    player.add_song("Stairway to Heaven - Led Zeppelin")
    player.add_song("Hotel California - Eagles")
    player.add_song("Sweet Child O' Mine - Guns N' Roses")
    player.add_song("Smells Like Teen Spirit - Nirvana")

    # Play all songs using the iterator
    player.play_all()

if __name__ == "__main__":
    main() 