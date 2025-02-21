#include "MusicStreamingService.hpp"
#include <iostream>
#include <algorithm>

MusicStreamingService::MusicStreamingService() : playlistIdCounter(1) {}

MusicStreamingService::~MusicStreamingService() {
    for (auto user : users) delete user;
    for (auto artist : artists) delete artist;
    for (auto song : songs) delete song;
}

void MusicStreamingService::addUser(User* user) {
    users.push_back(user);
}

void MusicStreamingService::addArtist(Artist* artist) {
    artists.push_back(artist);
}

void MusicStreamingService::addSong(Song* song, std::string artistId) {
    Artist* artist = findArtist(artistId);
    if (artist && artist->isActive()) {
        songs.push_back(song);
        artist->addSong(song);
    }
}

Playlist* MusicStreamingService::createPlaylist(std::string userId, std::string name,
                                              std::string description, bool isPublic) {
    User* user = findUser(userId);
    if (!user || !user->isActive()) return nullptr;
    
    Playlist* playlist = new Playlist(generatePlaylistId(), name, description, isPublic);
    user->addPlaylist(playlist);
    return playlist;
}

bool MusicStreamingService::addSongToPlaylist(std::string playlistId, std::string songId) {
    Playlist* playlist = findPlaylist(playlistId);
    Song* song = findSong(songId);
    
    if (playlist && song && song->isActive()) {
        playlist->addSong(song);
        return true;
    }
    return false;
}

bool MusicStreamingService::removeSongFromPlaylist(std::string playlistId, std::string songId) {
    Playlist* playlist = findPlaylist(playlistId);
    Song* song = findSong(songId);
    
    if (playlist && song) {
        playlist->removeSong(song);
        return true;
    }
    return false;
}

std::vector<Song*> MusicStreamingService::searchSongs(const std::string& query) const {
    std::vector<Song*> results;
    for (auto song : songs) {
        if (song->isActive() && 
            (song->getTitle().find(query) != std::string::npos ||
             song->getArtist().find(query) != std::string::npos ||
             song->getAlbum().find(query) != std::string::npos)) {
            results.push_back(song);
        }
    }
    return results;
}

std::vector<Artist*> MusicStreamingService::searchArtists(const std::string& query) const {
    std::vector<Artist*> results;
    for (auto artist : artists) {
        if (artist->isActive() && 
            (artist->getName().find(query) != std::string::npos ||
             artist->getBio().find(query) != std::string::npos)) {
            results.push_back(artist);
        }
    }
    return results;
}

std::vector<Playlist*> MusicStreamingService::searchPlaylists(const std::string& query) const {
    std::vector<Playlist*> results;
    for (auto user : users) {
        for (auto playlist : user->getPlaylists()) {
            if (playlist->getIsPublic() && 
                (playlist->getName().find(query) != std::string::npos ||
                 playlist->getDescription().find(query) != std::string::npos)) {
                results.push_back(playlist);
            }
        }
    }
    return results;
}

void MusicStreamingService::displayAllSongs() const {
    std::cout << "\nAll Songs:" << std::endl;
    for (const auto& song : songs) {
        if (song->isActive()) {
            song->displayInfo();
            std::cout << "------------------------" << std::endl;
        }
    }
}

void MusicStreamingService::displayAllArtists() const {
    std::cout << "\nAll Artists:" << std::endl;
    for (const auto& artist : artists) {
        if (artist->isActive()) {
            artist->displayInfo();
            std::cout << "------------------------" << std::endl;
        }
    }
}

void MusicStreamingService::displayUserPlaylists(std::string userId) const {
    User* user = findUser(userId);
    if (user && user->isActive()) {
        std::cout << "\nPlaylists for user " << user->getUsername() << ":" << std::endl;
        for (const auto& playlist : user->getPlaylists()) {
            playlist->displayInfo();
            std::cout << "------------------------" << std::endl;
        }
    }
}

void MusicStreamingService::displayArtistSongs(std::string artistId) const {
    Artist* artist = findArtist(artistId);
    if (artist && artist->isActive()) {
        artist->displayInfo();
    }
}

User* MusicStreamingService::findUser(const std::string& userId) const {
    auto it = std::find_if(users.begin(), users.end(),
        [&userId](const User* user) { return user->getUserId() == userId; });
    return it != users.end() ? *it : nullptr;
}

Artist* MusicStreamingService::findArtist(const std::string& artistId) const {
    auto it = std::find_if(artists.begin(), artists.end(),
        [&artistId](const Artist* artist) { return artist->getArtistId() == artistId; });
    return it != artists.end() ? *it : nullptr;
}

Song* MusicStreamingService::findSong(const std::string& songId) const {
    auto it = std::find_if(songs.begin(), songs.end(),
        [&songId](const Song* song) { return song->getSongId() == songId; });
    return it != songs.end() ? *it : nullptr;
}

Playlist* MusicStreamingService::findPlaylist(const std::string& playlistId) const {
    for (const auto& user : users) {
        for (const auto& playlist : user->getPlaylists()) {
            if (playlist->getPlaylistId() == playlistId) {
                return playlist;
            }
        }
    }
    return nullptr;
}

std::string MusicStreamingService::generatePlaylistId() {
    return "P" + std::to_string(playlistIdCounter++);
} 