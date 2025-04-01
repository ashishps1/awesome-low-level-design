from music_streaming_service import MusicStreamingService
from user import User
from song import Song
from album import Album
from artist import Artist
from music_player import MusicPlayer
from playlist import Playlist

class MusicStreamingServiceDemo:
    @staticmethod
    def run():
        music_streaming_service = MusicStreamingService()

        # Create users
        user1 = User("1", "john@example.com", "password123")
        user2 = User("2", "jane@example.com", "password456")

        # Create songs
        song1 = Song("1", "Song 1", "Artist 1", "Album 1", 180)
        song2 = Song("2", "Song 2", "Artist 2", "Album 2", 200)
        song3 = Song("3", "Song 3", "Artist 3", "Album 3", 210)

        # Create albums
        album1 = Album("1", "Album 1", "Artist 1", [song1])
        album2 = Album("2", "Album 2", "Artist 2", [song2])
        album3 = Album("3", "Album 3", "Artist 3", [song3])

        # Create artists
        artist1 = Artist("1", "Artist 1", [album1])
        artist2 = Artist("2", "Artist 2", [album2])
        artist3 = Artist("3", "Artist 3", [album3])

        # Add artists to the music library
        music_streaming_service.get_music_library().add_artist(artist1)
        music_streaming_service.get_music_library().add_artist(artist2)
        music_streaming_service.get_music_library().add_artist(artist3)

        # User registration
        music_streaming_service.get_user_manager().register_user(user1)
        music_streaming_service.get_user_manager().register_user(user2)

        # User login
        logged_in_user = music_streaming_service.get_user_manager().login_user("john@example.com", "password123")
        if logged_in_user:
            print(f"User logged in: {logged_in_user.username}")
        else:
            print("Invalid username or password.")

        # Search for songs
        search_results = music_streaming_service.get_music_library().search_songs("Song")
        print("Search Results:")
        for song in search_results:
            print(f"Song: {song.title} - {song.artist}")

        # Create a playlist
        playlist = Playlist("1", "My Playlist", logged_in_user)
        playlist.add_song(song1)
        playlist.add_song(song2)
        logged_in_user.add_playlist(playlist)

        # Get song recommendations
        recommendations = music_streaming_service.get_music_recommender().recommend_songs(logged_in_user)
        print("Recommended Songs:")
        for song in recommendations:
            print(f"Song: {song.title} - {song.artist}")

        # Play a song
        music_player = MusicPlayer()
        music_player.play_song(song1)

        # Pause the song
        music_player.pause_song()

        # Seek to a specific time
        music_player.seek_to(60)

        # Get user's playlists
        user_playlists = logged_in_user.get_playlists()
        print("User Playlists:")
        for user_playlist in user_playlists:
            print(f"Playlist: {user_playlist.name}")
            print("Songs:")
            for song in user_playlist.get_songs():
                print(f"- {song.title}")

if __name__ == "__main__":
    MusicStreamingServiceDemo.run()