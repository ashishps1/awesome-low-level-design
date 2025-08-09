from music_streaming_system import MusicStreamingSystem
from artist import Artist
from playable import Album
from user import User
from subscription_tier import SubscriptionTier
from command import PlayCommand, PauseCommand, NextTrackCommand
from playable import Playlist

class MusicStreamingDemo:
    @staticmethod
    def main():
        system = MusicStreamingSystem.get_instance()
        
        # --- Setup Catalog ---
        daft_punk = Artist("art1", "Daft Punk")
        system.add_artist(daft_punk)
        
        discovery = Album("Discovery")
        s1 = system.add_song("s1", "One More Time", daft_punk.id, 320)
        s2 = system.add_song("s2", "Aerodynamic", daft_punk.id, 212)
        s3 = system.add_song("s3", "Digital Love", daft_punk.id, 301)
        s4 = system.add_song("s4", "Radioactive", daft_punk.id, 311)
        discovery.add_track(s1)
        discovery.add_track(s2)
        discovery.add_track(s3)
        discovery.add_track(s4)
        
        # --- Register Users (Builder Pattern) ---
        free_user = User.Builder("Alice").with_subscription(SubscriptionTier.FREE, 0).build()
        premium_user = User.Builder("Bob").with_subscription(SubscriptionTier.PREMIUM, 0).build()
        system.register_user(free_user)
        system.register_user(premium_user)
        
        # --- Observer Pattern: User follows artist ---
        print("--- Observer Pattern Demo ---")
        premium_user.follow_artist(daft_punk)
        daft_punk.release_album(discovery)  # This will notify Bob
        print()
        
        # --- Strategy Pattern: Playback behavior ---
        print("--- Strategy Pattern (Free vs Premium) & State Pattern (Player) Demo ---")
        player = system.get_player()
        player.load(discovery, free_user)
        
        # --- Command Pattern: Controlling the player ---
        play = PlayCommand(player)
        pause = PauseCommand(player)
        next_track = NextTrackCommand(player)
        
        play.execute()  # Plays song 1
        next_track.execute()  # Plays song 2
        pause.execute()  # Pauses song 2
        play.execute()  # Resumes song 2
        next_track.execute()  # Plays song 3
        next_track.execute()  # Plays song 4 (ad for free user)
        print()
        
        # --- Premium user experience (no ads) ---
        print("--- Premium User Experience ---")
        player.load(discovery, premium_user)
        play.execute()
        next_track.execute()
        print()
        
        # --- Composite Pattern: Play a playlist ---
        print("--- Composite Pattern Demo ---")
        my_playlist = Playlist("My Awesome Mix")
        my_playlist.add_track(s3)  # Digital Love
        my_playlist.add_track(s1)  # One More Time
        
        player.load(my_playlist, premium_user)
        play.execute()
        next_track.execute()
        print()
        
        # --- Search and Recommendation ---
        print("--- Search and Recommendation Service Demo ---")
        search_results = system.search_songs_by_title("love")
        print(f"Search results for 'love': {search_results}")
        
        recommendations = system.get_song_recommendations()
        print(f"Your daily recommendations: {recommendations}")

if __name__ == "__main__":
    MusicStreamingDemo.main()