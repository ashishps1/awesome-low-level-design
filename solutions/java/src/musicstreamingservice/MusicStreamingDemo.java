package musicstreamingservice;


import musicstreamingservice.command.NextTrackCommand;
import musicstreamingservice.command.PauseCommand;
import musicstreamingservice.command.PlayCommand;
import musicstreamingservice.enums.SubscriptionTier;
import musicstreamingservice.entities.*;

import java.util.List;

public class MusicStreamingDemo {
    public static void main(String[] args) throws InterruptedException {
        MusicStreamingSystem system = MusicStreamingSystem.getInstance();

        // --- Setup Catalog ---
        Artist daftPunk = new Artist("art1", "Daft Punk");
        system.addArtist(daftPunk);

        Album discovery = new Album("Discovery");
        Song s1 = system.addSong("s1", "One More Time", daftPunk.getId(), 320);
        Song s2 = system.addSong("s2", "Aerodynamic", daftPunk.getId(), 212);
        Song s3 = system.addSong("s3", "Digital Love", daftPunk.getId(), 301);
        Song s4 = system.addSong("s4", "Radioactive", daftPunk.getId(), 311);
        discovery.addTrack(s1);
        discovery.addTrack(s2);
        discovery.addTrack(s3);
        discovery.addTrack(s4);

        // --- Register Users (Builder Pattern) ---
        User freeUser = new User.Builder("Alice").withSubscription(SubscriptionTier.FREE, 0).build();
        User premiumUser = new User.Builder("Bob").withSubscription(SubscriptionTier.PREMIUM, 0).build();
        system.registerUser(freeUser);
        system.registerUser(premiumUser);

        // --- Observer Pattern: User follows artist ---
        System.out.println("--- Observer Pattern Demo ---");
        premiumUser.followArtist(daftPunk);
        daftPunk.releaseAlbum(discovery); // This will notify Bob
        System.out.println();

        // --- Strategy Pattern: Playback behavior ---
        System.out.println("--- Strategy Pattern (Free vs Premium) & State Pattern (Player) Demo ---");
        Player player = system.getPlayer();
        player.load(discovery, freeUser);

        // --- Command Pattern: Controlling the player ---
        PlayCommand play = new PlayCommand(player);
        PauseCommand pause = new PauseCommand(player);
        NextTrackCommand next = new NextTrackCommand(player);

        play.execute(); // Plays song 1
        next.execute(); // Plays song 2
        pause.execute(); // Pauses song 2
        play.execute(); // Resumes song 2
        next.execute(); // Plays song 3
        next.execute(); // Plays song 4 (ad for free user)
        System.out.println();

        // --- Premium user experience (no ads) ---
        System.out.println("--- Premium User Experience ---");
        player.load(discovery, premiumUser);
        play.execute();
        next.execute();
        System.out.println();

        // --- Composite Pattern: Play a playlist ---
        System.out.println("--- Composite Pattern Demo ---");
        Playlist myPlaylist = new Playlist("My Awesome Mix");
        myPlaylist.addTrack(s3); // Digital Love
        myPlaylist.addTrack(s1); // One More Time

        player.load(myPlaylist, premiumUser);
        play.execute();
        next.execute();
        System.out.println();

        // --- Search and Recommendation ---
        System.out.println("--- Search and Recommendation Service Demo ---");
        List<Song> searchResults = system.searchSongsByTitle("love");
        System.out.println("Search results for 'love': " + searchResults);

        List<Song> recommendations = system.getSongRecommendations();
        System.out.println("Your daily recommendations: " + recommendations);
    }
}
