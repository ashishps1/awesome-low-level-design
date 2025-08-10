using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

public class MusicStreamingDemo
{
    public static void Main(string[] args)
    {
        MusicStreamingSystem system = MusicStreamingSystem.GetInstance();

        // --- Setup Catalog ---
        Artist daftPunk = new Artist("art1", "Daft Punk");
        system.AddArtist(daftPunk);

        Album discovery = new Album("Discovery");
        Song s1 = system.AddSong("s1", "One More Time", daftPunk.GetId(), 320);
        Song s2 = system.AddSong("s2", "Aerodynamic", daftPunk.GetId(), 212);
        Song s3 = system.AddSong("s3", "Digital Love", daftPunk.GetId(), 301);
        Song s4 = system.AddSong("s4", "Radioactive", daftPunk.GetId(), 311);
        discovery.AddTrack(s1);
        discovery.AddTrack(s2);
        discovery.AddTrack(s3);
        discovery.AddTrack(s4);

        // --- Register Users (Builder Pattern) ---
        User freeUser = new UserBuilder("Alice").WithSubscription(SubscriptionTier.FREE, 0).Build();
        User premiumUser = new UserBuilder("Bob").WithSubscription(SubscriptionTier.PREMIUM, 0).Build();
        system.RegisterUser(freeUser);
        system.RegisterUser(premiumUser);

        // --- Observer Pattern: User follows artist ---
        Console.WriteLine("--- Observer Pattern Demo ---");
        premiumUser.FollowArtist(daftPunk);
        daftPunk.ReleaseAlbum(discovery); // This will notify Bob
        Console.WriteLine();

        // --- Strategy Pattern: Playback behavior ---
        Console.WriteLine("--- Strategy Pattern (Free vs Premium) & State Pattern (Player) Demo ---");
        Player player = system.GetPlayer();
        player.Load(discovery, freeUser);

        // --- Command Pattern: Controlling the player ---
        ICommand play = new PlayCommand(player);
        ICommand pause = new PauseCommand(player);
        ICommand nextTrack = new NextTrackCommand(player);

        play.Execute(); // Plays song 1
        nextTrack.Execute(); // Plays song 2
        pause.Execute(); // Pauses song 2
        play.Execute(); // Resumes song 2
        nextTrack.Execute(); // Plays song 3
        nextTrack.Execute(); // Plays song 4 (ad for free user)
        Console.WriteLine();

        // --- Premium user experience (no ads) ---
        Console.WriteLine("--- Premium User Experience ---");
        player.Load(discovery, premiumUser);
        play.Execute();
        nextTrack.Execute();
        Console.WriteLine();

        // --- Composite Pattern: Play a playlist ---
        Console.WriteLine("--- Composite Pattern Demo ---");
        Playlist myPlaylist = new Playlist("My Awesome Mix");
        myPlaylist.AddTrack(s3); // Digital Love
        myPlaylist.AddTrack(s1); // One More Time

        player.Load(myPlaylist, premiumUser);
        play.Execute();
        nextTrack.Execute();
        Console.WriteLine();

        // --- Search and Recommendation ---
        Console.WriteLine("--- Search and Recommendation Service Demo ---");
        List<Song> searchResults = system.SearchSongsByTitle("love");
        Console.WriteLine($"Search results for 'love': {string.Join(", ", searchResults)}");

        List<Song> recommendations = system.GetSongRecommendations();
        Console.WriteLine($"Your daily recommendations: {string.Join(", ", recommendations)}");
    }
}