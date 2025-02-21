#include "Artist.hpp"
#include <iostream>
#include <algorithm>

Artist::Artist(std::string artistId, std::string name, std::string bio)
    : artistId(artistId), name(name), bio(bio), active(true) {}

Artist::~Artist() {
    for (auto song : songs) {
        delete song;
    }
}

std::string Artist::getArtistId() const { return artistId; }
std::string Artist::getName() const { return name; }
std::string Artist::getBio() const { return bio; }
bool Artist::isActive() const { return active; }
const std::vector<Song*>& Artist::getSongs() const { return songs; }

void Artist::addSong(Song* song) {
    songs.push_back(song);
}

void Artist::removeSong(Song* song) {
    auto it = std::find(songs.begin(), songs.end(), song);
    if (it != songs.end()) {
        delete *it;
        songs.erase(it);
    }
}

void Artist::setActive(bool status) {
    active = status;
}

void Artist::displayInfo() const {
    std::cout << "Artist: " << name << " (ID: " << artistId << ")" << std::endl;
    std::cout << "Bio: " << bio << std::endl;
    std::cout << "Status: " << (active ? "Active" : "Inactive") << std::endl;
    std::cout << "Number of Songs: " << songs.size() << std::endl;
    
    if (!songs.empty()) {
        std::cout << "\nSongs:" << std::endl;
        for (const auto& song : songs) {
            std::cout << "- " << song->getTitle() << " (" << song->getAlbum() << ")" << std::endl;
        }
    }
} 