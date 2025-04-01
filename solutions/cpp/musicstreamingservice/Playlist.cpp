#include "Playlist.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>

Playlist::Playlist(std::string playlistId, std::string name, std::string description,
                  bool isPublic)
    : playlistId(playlistId), name(name), description(description),
      isPublic(isPublic) {}

std::string Playlist::getPlaylistId() const { return playlistId; }
std::string Playlist::getName() const { return name; }
std::string Playlist::getDescription() const { return description; }
bool Playlist::getIsPublic() const { return isPublic; }
const std::vector<Song*>& Playlist::getSongs() const { return songs; }

void Playlist::addSong(Song* song) {
    if (song && song->isActive()) {
        songs.push_back(song);
    }
}

void Playlist::removeSong(Song* song) {
    auto it = std::find(songs.begin(), songs.end(), song);
    if (it != songs.end()) {
        songs.erase(it);
    }
}

void Playlist::setPublic(bool isPublic) {
    this->isPublic = isPublic;
}

int Playlist::getTotalDuration() const {
    int total = 0;
    for (const auto& song : songs) {
        total += song->getDurationSeconds();
    }
    return total;
}

void Playlist::displayInfo() const {
    std::cout << "\nPlaylist: " << name << " (ID: " << playlistId << ")" << std::endl;
    std::cout << "Description: " << description << std::endl;
    std::cout << "Visibility: " << (isPublic ? "Public" : "Private") << std::endl;
    std::cout << "Number of Songs: " << songs.size() << std::endl;
    
    int totalDuration = getTotalDuration();
    int minutes = totalDuration / 60;
    int seconds = totalDuration % 60;
    std::cout << "Total Duration: " << minutes << ":" 
              << std::setfill('0') << std::setw(2) << seconds << std::endl;
    
    if (!songs.empty()) {
        std::cout << "\nSongs:" << std::endl;
        for (const auto& song : songs) {
            std::cout << "- " << song->getTitle() << " by " << song->getArtist() << std::endl;
        }
    }
} 