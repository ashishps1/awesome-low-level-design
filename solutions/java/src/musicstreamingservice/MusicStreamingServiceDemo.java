package musicstreamingservice;

import java.util.Arrays;
import java.util.List;

public class MusicStreamingServiceDemo {
    public static void run() {
        MusicStreamingService musicStreamingService = new MusicStreamingService();

        // Create users
        User user1 = new User("1", "john@example.com", "password123");
        User user2 = new User("2", "jane@example.com", "password456");

        // Create songs
        Song song1 = new Song("1", "Song 1", "Artist 1", "Album 1", 180);
        Song song2 = new Song("2", "Song 2", "Artist 2", "Album 2", 200);
        Song song3 = new Song("3", "Song 3", "Artist 3", "Album 3", 210);

        // Create albums
        Album album1 = new Album("1", "Album 1", "Artist 1", List.of(song1));
        Album album2 = new Album("2", "Album 2", "Artist 2", List.of(song2));
        Album album3 = new Album("3", "Album 3", "Artist 3", List.of(song3));

        // Create artists
        Artist artist1 = new Artist("1", "Artist 1", List.of(album1));
        Artist artist2 = new Artist("2", "Artist 2", List.of(album2));
        Artist artist3 = new Artist("3", "Artist 3", List.of(album3));

        // Add artists to the music library
        musicStreamingService.getMusicLibrary().addArtist(artist1);
        musicStreamingService.getMusicLibrary().addArtist(artist2);
        musicStreamingService.getMusicLibrary().addArtist(artist3);

        // User registration
        musicStreamingService.getUserManager().registerUser(user1);
        musicStreamingService.getUserManager().registerUser(user2);

        // User login
        User loggedInUser = musicStreamingService.getUserManager().loginUser("john@example.com", "password123");
        if (loggedInUser != null) {
            System.out.println("User logged in: " + loggedInUser.getUsername());
        } else {
            System.out.println("Invalid username or password.");
        }

        // Search for songs
        List<Song> searchResults = musicStreamingService.getMusicLibrary().searchSongs("Song");
        System.out.println("Search Results:");
        for (Song song : searchResults) {
            System.out.println("Song: " + song.getTitle() + " - " + song.getArtist());
        }

        // Create a playlist
        Playlist playlist = new Playlist("1", "My Playlist", loggedInUser);
        playlist.addSong(song1);
        playlist.addSong(song2);
        loggedInUser.addPlaylist(playlist);

        // Get song recommendations
        List<Song> recommendations = musicStreamingService.getMusicRecommender().recommendSongs(loggedInUser);
        System.out.println("Recommended Songs:");
        for (Song song : recommendations) {
            System.out.println("Song: " + song.getTitle() + " - " + song.getArtist());
        }

        // Play a song
        MusicPlayer musicPlayer = new MusicPlayer();
        musicPlayer.playSong(song1);

        // Pause the song
        musicPlayer.pauseSong();

        // Seek to a specific time
        musicPlayer.seekTo(60);

        // Get user's playlists
        List<Playlist> userPlaylists = loggedInUser.getPlaylists();
        System.out.println("User Playlists:");
        for (Playlist userPlaylist : userPlaylists) {
            System.out.println("Playlist: " + userPlaylist.getName());
            System.out.println("Songs:");
            for (Song song : userPlaylist.getSongs()) {
                System.out.println("- " + song.getTitle());
            }
        }
    }
}
