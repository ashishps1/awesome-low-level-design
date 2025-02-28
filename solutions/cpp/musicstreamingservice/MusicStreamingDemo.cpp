#include "MusicStreamingService.hpp"
#include <iostream>

int main() {
    MusicStreamingService service;
    
    // Create users
    User* user1 = new User("U001", "john_doe", "john@email.com");
    User* user2 = new User("U002", "jane_smith", "jane@email.com", UserType::PREMIUM);
    service.addUser(user1);
    service.addUser(user2);
    
    // Create artists
    Artist* artist1 = new Artist("A001", "The Beatles", "Legendary British rock band");
    Artist* artist2 = new Artist("A002", "Queen", "Iconic rock band led by Freddie Mercury");
    service.addArtist(artist1);
    service.addArtist(artist2);
    
    // Add songs
    Song* song1 = new Song("S001", "Hey Jude", "The Beatles", "The Beatles", 
                          Genre::ROCK, 431, "path/to/hey_jude.mp3");
    Song* song2 = new Song("S002", "Let It Be", "The Beatles", "Let It Be",
                          Genre::ROCK, 243, "path/to/let_it_be.mp3");
    Song* song3 = new Song("S003", "Bohemian Rhapsody", "Queen", "A Night at the Opera",
                          Genre::ROCK, 354, "path/to/bohemian_rhapsody.mp3");
    
    service.addSong(song1, "A001");
    service.addSong(song2, "A001");
    service.addSong(song3, "A002");
    
    // Display all songs and artists
    std::cout << "Initial catalog:" << std::endl;
    service.displayAllSongs();
    service.displayAllArtists();
    
    // Create playlists
    Playlist* playlist1 = service.createPlaylist("U001", "Rock Classics",
                                               "Best rock songs of all time");
    if (playlist1) {
        service.addSongToPlaylist(playlist1->getPlaylistId(), "S001");
        service.addSongToPlaylist(playlist1->getPlaylistId(), "S003");
    }
    
    Playlist* playlist2 = service.createPlaylist("U002", "Beatles Only",
                                               "Beatles songs collection", false);
    if (playlist2) {
        service.addSongToPlaylist(playlist2->getPlaylistId(), "S001");
        service.addSongToPlaylist(playlist2->getPlaylistId(), "S002");
    }
    
    // Display user playlists
    std::cout << "\nUser Playlists:" << std::endl;
    service.displayUserPlaylists("U001");
    service.displayUserPlaylists("U002");
    
    // Search functionality
    std::cout << "\nSearching for 'Beatles':" << std::endl;
    auto songResults = service.searchSongs("Beatles");
    for (const auto& song : songResults) {
        song->displayInfo();
    }
    
    // Remove song from playlist
    std::cout << "\nRemoving 'Hey Jude' from Rock Classics playlist..." << std::endl;
    if (service.removeSongFromPlaylist(playlist1->getPlaylistId(), "S001")) {
        std::cout << "Song removed successfully" << std::endl;
        service.displayUserPlaylists("U001");
    }
    
    // Upgrade user to premium
    std::cout << "\nUpgrading user john_doe to premium..." << std::endl;
    user1->upgradeToPremuim();
    user1->displayInfo();
    
    return 0;
} 