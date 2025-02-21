#ifndef SONG_HPP
#define SONG_HPP

#include <string>
#include <vector>

enum class Genre {
    POP,
    ROCK,
    JAZZ,
    CLASSICAL,
    HIPHOP,
    ELECTRONIC
};

class Song {
private:
    std::string songId;
    std::string title;
    std::string artist;
    std::string album;
    Genre genre;
    int durationSeconds;
    std::string filePath;
    bool active;

public:
    Song(std::string songId, std::string title, std::string artist,
         std::string album, Genre genre, int durationSeconds,
         std::string filePath);
    
    std::string getSongId() const;
    std::string getTitle() const;
    std::string getArtist() const;
    std::string getAlbum() const;
    Genre getGenre() const;
    int getDurationSeconds() const;
    std::string getFilePath() const;
    bool isActive() const;
    
    void setActive(bool status);
    void displayInfo() const;
};

#endif 