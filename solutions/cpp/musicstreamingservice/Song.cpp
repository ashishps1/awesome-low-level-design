#include "Song.hpp"
#include <iostream>
#include <iomanip>

Song::Song(std::string songId, std::string title, std::string artist,
           std::string album, Genre genre, int durationSeconds,
           std::string filePath)
    : songId(songId), title(title), artist(artist), album(album),
      genre(genre), durationSeconds(durationSeconds), filePath(filePath),
      active(true) {}

std::string Song::getSongId() const { return songId; }
std::string Song::getTitle() const { return title; }
std::string Song::getArtist() const { return artist; }
std::string Song::getAlbum() const { return album; }
Genre Song::getGenre() const { return genre; }
int Song::getDurationSeconds() const { return durationSeconds; }
std::string Song::getFilePath() const { return filePath; }
bool Song::isActive() const { return active; }

void Song::setActive(bool status) {
    active = status;
}

void Song::displayInfo() const {
    std::cout << "Song: " << title << " (ID: " << songId << ")" << std::endl;
    std::cout << "Artist: " << artist << std::endl;
    std::cout << "Album: " << album << std::endl;
    std::cout << "Genre: ";
    switch (genre) {
        case Genre::POP: std::cout << "Pop"; break;
        case Genre::ROCK: std::cout << "Rock"; break;
        case Genre::JAZZ: std::cout << "Jazz"; break;
        case Genre::CLASSICAL: std::cout << "Classical"; break;
        case Genre::HIPHOP: std::cout << "Hip Hop"; break;
        case Genre::ELECTRONIC: std::cout << "Electronic"; break;
    }
    std::cout << std::endl;
    
    int minutes = durationSeconds / 60;
    int seconds = durationSeconds % 60;
    std::cout << "Duration: " << minutes << ":" 
              << std::setfill('0') << std::setw(2) << seconds << std::endl;
    std::cout << "Status: " << (active ? "Active" : "Inactive") << std::endl;
} 