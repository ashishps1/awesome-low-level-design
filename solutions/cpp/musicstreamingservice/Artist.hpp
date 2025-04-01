#ifndef ARTIST_HPP
#define ARTIST_HPP

#include <string>
#include <vector>
#include "Song.hpp"

class Artist {
private:
    std::string artistId;
    std::string name;
    std::string bio;
    std::vector<Song*> songs;
    bool active;

public:
    Artist(std::string artistId, std::string name, std::string bio);
    ~Artist();
    
    std::string getArtistId() const;
    std::string getName() const;
    std::string getBio() const;
    bool isActive() const;
    const std::vector<Song*>& getSongs() const;
    
    void addSong(Song* song);
    void removeSong(Song* song);
    void setActive(bool status);
    void displayInfo() const;
};

#endif 