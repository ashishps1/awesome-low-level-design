#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP

#include <string>
#include <vector>
#include "Song.hpp"

class Playlist {
private:
    std::string playlistId;
    std::string name;
    std::string description;
    std::vector<Song*> songs;
    bool isPublic;

public:
    Playlist(std::string playlistId, std::string name, std::string description,
            bool isPublic = true);
    
    std::string getPlaylistId() const;
    std::string getName() const;
    std::string getDescription() const;
    bool getIsPublic() const;
    const std::vector<Song*>& getSongs() const;
    
    void addSong(Song* song);
    void removeSong(Song* song);
    void setPublic(bool isPublic);
    int getTotalDuration() const;
    void displayInfo() const;
};

#endif 