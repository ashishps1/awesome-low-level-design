using System;
using System.Collections.Generic;

namespace MusicStreamingService
{
    public class MusicStreamingServiceDemo
    {
        public static void Run()
        {
            var musicStreamingService = new MusicStreamingService();

            // Create users
            var user1 = new User("1", "john@example.com", "password123");
            var user2 = new User("2", "jane@example.com", "password456");

            // Create songs
            var song1 = new Song("1", "Song 1", "Artist 1", "Album 1", 180);
            var song2 = new Song("2", "Song 2", "Artist 2", "Album 2", 200);
            var song3 = new Song("3", "Song 3", "Artist 3", "Album 3", 210);

            // Create albums
            var album1 = new Album("1", "Album 1", "Artist 1", new List<Song> { song1 });
            var album2 = new Album("2", "Album 2", "Artist 2", new List<Song> { song2 });
            var album3 = new Album("3", "Album 3", "Artist 3", new List<Song> { song3 });

            // Create artists
            var artist1 = new Artist("1", "Artist 1", new List<Album> { album1 });
            var artist2 = new Artist("2", "Artist 2", new List<Album> { album2 });
            var artist3 = new Artist("3", "Artist 3", new List<Album> { album3 });

            // Add artists to the music library
            musicStreamingService.MusicLibrary.AddArtist(artist1);
            musicStreamingService.MusicLibrary.AddArtist(artist2);
            musicStreamingService.MusicLibrary.AddArtist(artist3);

            // User registration
            musicStreamingService.UserManager.RegisterUser(user1);
            musicStreamingService.UserManager.RegisterUser(user2);

            // User login
            var loggedInUser = musicStreamingService.UserManager.LoginUser("john@example.com", "password123");
            if (loggedInUser != null)
            {
                Console.WriteLine("User logged in: " + loggedInUser.Username);
            }
            else
            {
                Console.WriteLine("Invalid username or password.");
            }

            // Search for songs
            var searchResults = musicStreamingService.MusicLibrary.SearchSongs("Song");
            Console.WriteLine("Search Results:");
            foreach (var song in searchResults)
            {
                Console.WriteLine("Song: " + song.Title + " - " + song.Artist);
            }

            // Create a playlist
            var playlist = new Playlist("1", "My Playlist", loggedInUser);
            playlist.AddSong(song1);
            playlist.AddSong(song2);
            loggedInUser.AddPlaylist(playlist);

            // Get song recommendations
            var recommendations = musicStreamingService.MusicRecommender.RecommendSongs(loggedInUser);
            Console.WriteLine("Recommended Songs:");
            foreach (var song in recommendations)
            {
                Console.WriteLine("Song: " + song.Title + " - " + song.Artist);
            }

            // Play a song
            var musicPlayer = new MusicPlayer();
            musicPlayer.PlaySong(song1);

            // Pause the song
            musicPlayer.PauseSong();

            // Seek to a specific time
            musicPlayer.SeekTo(60);

            // Get user's playlists
            var userPlaylists = loggedInUser.Playlists;
            Console.WriteLine("User Playlists:");
            foreach (var userPlaylist in userPlaylists)
            {
                Console.WriteLine("Playlist: " + userPlaylist.Name);
                Console.WriteLine("Songs:");
                foreach (var song in userPlaylist.Songs)
                {
                    Console.WriteLine("- " + song.Title);
                }
            }
        }
    }
}