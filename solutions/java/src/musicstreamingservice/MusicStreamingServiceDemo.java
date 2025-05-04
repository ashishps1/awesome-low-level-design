package musicstreamingservice;

import java.time.Duration;
import java.util.List;

public class MusicStreamingServiceDemo {
    public static void run() {
        MusicStreamingService musicStreamingService = new MusicStreamingService();

        // Create users
        User user1 = musicStreamingService.registerUser( "john@example.com", "password123");
        User user2 = musicStreamingService.registerUser( "jane@example.com", "password456");

        // Create artists
        Artist artist1 = musicStreamingService.addNewArtist("Artist 1");
        Artist artist2 = musicStreamingService.addNewArtist("Artist 2");

        // Create albums
        Album album1 = musicStreamingService.addNewAlbum("Album 1", artist1.getId());
        Album album2 = musicStreamingService.addNewAlbum("Album 2", artist2.getId());

        // Create songs
        Song song1 = musicStreamingService.addNewSong("Song 1", artist1.getId(), album1.getId(), Duration.ofMinutes(4));
        Song song2 = musicStreamingService.addNewSong("Song 2", artist2.getId(), album2.getId(), Duration.ofMinutes(3));
        Song song3 = musicStreamingService.addNewSong("Song 3", artist2.getId(), album2.getId(), Duration.ofMinutes(5));

        // Add albums to artists
        musicStreamingService.addAlbumToArtist(artist1.getId(), album1.getId());
        musicStreamingService.addAlbumToArtist(artist2.getId(), album2.getId());

        // Add songs to albums
        musicStreamingService.addSongsToAlbum(album1.getId(), List.of(song1.getId(), song2.getId()));
        musicStreamingService.addSongsToAlbum(album2.getId(), List.of(song3.getId()));

        // Create playlists
        Playlist playlist1 = musicStreamingService.createPlaylist(user1.getId(), "Playlist 1");
        Playlist playlist2 = musicStreamingService.createPlaylist(user1.getId(), "Playlist 2");

        // Add songs to playlist
        musicStreamingService.addSongToPlaylist(user1.getId(), playlist1.getId(), song1.getId());
        musicStreamingService.addSongToPlaylist(user1.getId(), playlist1.getId(), song2.getId());

        // Search for songs
        List<Song> searchResults = musicStreamingService.searchSongs("Song");
        System.out.println("Search Results:");
        for (Song song : searchResults) {
            System.out.println("Song: " + song.getTitle() + " - " + song.getArtistName());
        }

        // Play a song
        musicStreamingService.playSong(user2.getId(), song1.getId());

        // Pause the song
        musicStreamingService.pauseSong(user2.getId());
    }
}
