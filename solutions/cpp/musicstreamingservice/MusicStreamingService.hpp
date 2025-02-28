#ifndef MUSIC_STREAMING_SERVICE_HPP
#define MUSIC_STREAMING_SERVICE_HPP

#include <vector>
#include <string>
#include "User.hpp"
#include "Artist.hpp"
#include "Song.hpp"
#include "Playlist.hpp"

class MusicStreamingService {
private:
    std::vector<User*> users;
    std::vector<Artist*> artists;
    std::vector<Song*> songs;
    int playlistIdCounter;

public:
    MusicStreamingService();
    ~MusicStreamingService();
    
    void addUser(User* user);
    void addArtist(Artist* artist);
    void addSong(Song* song, std::string artistId);
    
    Playlist* createPlaylist(std::string userId, std::string name,
                           std::string description, bool isPublic = true);
    bool addSongToPlaylist(std::string playlistId, std::string songId);
    bool removeSongFromPlaylist(std::string playlistId, std::string songId);
    
    std::vector<Song*> searchSongs(const std::string& query) const;
    std::vector<Artist*> searchArtists(const std::string& query) const;
    std::vector<Playlist*> searchPlaylists(const std::string& query) const;
    
    void displayAllSongs() const;
    void displayAllArtists() const;
    void displayUserPlaylists(std::string userId) const;
    void displayArtistSongs(std::string artistId) const;
    
private:
    User* findUser(const std::string& userId) const;
    Artist* findArtist(const std::string& artistId) const;
    Song* findSong(const std::string& songId) const;
    Playlist* findPlaylist(const std::string& playlistId) const;
    std::string generatePlaylistId();
};

#endif 