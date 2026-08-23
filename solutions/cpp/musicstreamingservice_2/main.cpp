// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ----- forward declarations -----
class Song;
class Artist;
class Playlist;
class User;
class MusicStreamingService;

// ===== Song.hpp =====
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
    string songId;
    string title;
    string artist;
    string album;
    Genre genre;
    int durationSeconds;
    string filePath;
    bool active;

public:
    Song(string songId, string title, string artist,
         string album, Genre genre, int durationSeconds,
         string filePath);
    
    string getSongId() const;
    string getTitle() const;
    string getArtist() const;
    string getAlbum() const;
    Genre getGenre() const;
    int getDurationSeconds() const;
    string getFilePath() const;
    bool isActive() const;
    
    void setActive(bool status);
    void displayInfo() const;
};

// ===== Artist.hpp =====
class Artist {
private:
    string artistId;
    string name;
    string bio;
    vector<Song*> songs;
    bool active;

public:
    Artist(string artistId, string name, string bio);
    ~Artist();
    
    string getArtistId() const;
    string getName() const;
    string getBio() const;
    bool isActive() const;
    const vector<Song*>& getSongs() const;
    
    void addSong(Song* song);
    void removeSong(Song* song);
    void setActive(bool status);
    void displayInfo() const;
};

// ===== Playlist.hpp =====
class Playlist {
private:
    string playlistId;
    string name;
    string description;
    vector<Song*> songs;
    bool isPublic;

public:
    Playlist(string playlistId, string name, string description,
            bool isPublic = true);
    
    string getPlaylistId() const;
    string getName() const;
    string getDescription() const;
    bool getIsPublic() const;
    const vector<Song*>& getSongs() const;
    
    void addSong(Song* song);
    void removeSong(Song* song);
    void setPublic(bool isPublic);
    int getTotalDuration() const;
    void displayInfo() const;
};

// ===== User.hpp =====
enum class UserType {
    FREE,
    PREMIUM
};

class User {
private:
    string userId;
    string username;
    string email;
    UserType type;
    vector<Playlist*> playlists;
    bool active;

public:
    User(string userId, string username, string email,
         UserType type = UserType::FREE);
    ~User();
    
    string getUserId() const;
    string getUsername() const;
    string getEmail() const;
    UserType getType() const;
    bool isActive() const;
    const vector<Playlist*>& getPlaylists() const;
    
    void addPlaylist(Playlist* playlist);
    void removePlaylist(Playlist* playlist);
    void upgradeToPremuim();
    void setActive(bool status);
    void displayInfo() const;
};

// ===== MusicStreamingService.hpp =====
class MusicStreamingService {
private:
    vector<User*> users;
    vector<Artist*> artists;
    vector<Song*> songs;
    int playlistIdCounter;

public:
    MusicStreamingService();
    ~MusicStreamingService();
    
    void addUser(User* user);
    void addArtist(Artist* artist);
    void addSong(Song* song, string artistId);
    
    Playlist* createPlaylist(string userId, string name,
                           string description, bool isPublic = true);
    bool addSongToPlaylist(string playlistId, string songId);
    bool removeSongFromPlaylist(string playlistId, string songId);
    
    vector<Song*> searchSongs(const string& query) const;
    vector<Artist*> searchArtists(const string& query) const;
    vector<Playlist*> searchPlaylists(const string& query) const;
    
    void displayAllSongs() const;
    void displayAllArtists() const;
    void displayUserPlaylists(string userId) const;
    void displayArtistSongs(string artistId) const;
    
private:
    User* findUser(const string& userId) const;
    Artist* findArtist(const string& artistId) const;
    Song* findSong(const string& songId) const;
    Playlist* findPlaylist(const string& playlistId) const;
    string generatePlaylistId();
};

// ===== Artist.cpp =====
Artist::Artist(string artistId, string name, string bio)
    : artistId(artistId), name(name), bio(bio), active(true) {}

Artist::~Artist() {
    for (auto song : songs) {
        delete song;
    }
}

string Artist::getArtistId() const { return artistId; }
string Artist::getName() const { return name; }
string Artist::getBio() const { return bio; }
bool Artist::isActive() const { return active; }
const vector<Song*>& Artist::getSongs() const { return songs; }

void Artist::addSong(Song* song) {
    songs.push_back(song);
}

void Artist::removeSong(Song* song) {
    auto it = find(songs.begin(), songs.end(), song);
    if (it != songs.end()) {
        delete *it;
        songs.erase(it);
    }
}

void Artist::setActive(bool status) {
    active = status;
}

void Artist::displayInfo() const {
    cout << "Artist: " << name << " (ID: " << artistId << ")" << endl;
    cout << "Bio: " << bio << endl;
    cout << "Status: " << (active ? "Active" : "Inactive") << endl;
    cout << "Number of Songs: " << songs.size() << endl;
    
    if (!songs.empty()) {
        cout << "\nSongs:" << endl;
        for (const auto& song : songs) {
            cout << "- " << song->getTitle() << " (" << song->getAlbum() << ")" << endl;
        }
    }
} 

// ===== MusicStreamingService.cpp =====
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

void MusicStreamingService::addSong(Song* song, string artistId) {
    Artist* artist = findArtist(artistId);
    if (artist && artist->isActive()) {
        songs.push_back(song);
        artist->addSong(song);
    }
}

Playlist* MusicStreamingService::createPlaylist(string userId, string name,
                                              string description, bool isPublic) {
    User* user = findUser(userId);
    if (!user || !user->isActive()) return nullptr;
    
    Playlist* playlist = new Playlist(generatePlaylistId(), name, description, isPublic);
    user->addPlaylist(playlist);
    return playlist;
}

bool MusicStreamingService::addSongToPlaylist(string playlistId, string songId) {
    Playlist* playlist = findPlaylist(playlistId);
    Song* song = findSong(songId);
    
    if (playlist && song && song->isActive()) {
        playlist->addSong(song);
        return true;
    }
    return false;
}

bool MusicStreamingService::removeSongFromPlaylist(string playlistId, string songId) {
    Playlist* playlist = findPlaylist(playlistId);
    Song* song = findSong(songId);
    
    if (playlist && song) {
        playlist->removeSong(song);
        return true;
    }
    return false;
}

vector<Song*> MusicStreamingService::searchSongs(const string& query) const {
    vector<Song*> results;
    for (auto song : songs) {
        if (song->isActive() && 
            (song->getTitle().find(query) != string::npos ||
             song->getArtist().find(query) != string::npos ||
             song->getAlbum().find(query) != string::npos)) {
            results.push_back(song);
        }
    }
    return results;
}

vector<Artist*> MusicStreamingService::searchArtists(const string& query) const {
    vector<Artist*> results;
    for (auto artist : artists) {
        if (artist->isActive() && 
            (artist->getName().find(query) != string::npos ||
             artist->getBio().find(query) != string::npos)) {
            results.push_back(artist);
        }
    }
    return results;
}

vector<Playlist*> MusicStreamingService::searchPlaylists(const string& query) const {
    vector<Playlist*> results;
    for (auto user : users) {
        for (auto playlist : user->getPlaylists()) {
            if (playlist->getIsPublic() && 
                (playlist->getName().find(query) != string::npos ||
                 playlist->getDescription().find(query) != string::npos)) {
                results.push_back(playlist);
            }
        }
    }
    return results;
}

void MusicStreamingService::displayAllSongs() const {
    cout << "\nAll Songs:" << endl;
    for (const auto& song : songs) {
        if (song->isActive()) {
            song->displayInfo();
            cout << "------------------------" << endl;
        }
    }
}

void MusicStreamingService::displayAllArtists() const {
    cout << "\nAll Artists:" << endl;
    for (const auto& artist : artists) {
        if (artist->isActive()) {
            artist->displayInfo();
            cout << "------------------------" << endl;
        }
    }
}

void MusicStreamingService::displayUserPlaylists(string userId) const {
    User* user = findUser(userId);
    if (user && user->isActive()) {
        cout << "\nPlaylists for user " << user->getUsername() << ":" << endl;
        for (const auto& playlist : user->getPlaylists()) {
            playlist->displayInfo();
            cout << "------------------------" << endl;
        }
    }
}

void MusicStreamingService::displayArtistSongs(string artistId) const {
    Artist* artist = findArtist(artistId);
    if (artist && artist->isActive()) {
        artist->displayInfo();
    }
}

User* MusicStreamingService::findUser(const string& userId) const {
    auto it = find_if(users.begin(), users.end(),
        [&userId](const User* user) { return user->getUserId() == userId; });
    return it != users.end() ? *it : nullptr;
}

Artist* MusicStreamingService::findArtist(const string& artistId) const {
    auto it = find_if(artists.begin(), artists.end(),
        [&artistId](const Artist* artist) { return artist->getArtistId() == artistId; });
    return it != artists.end() ? *it : nullptr;
}

Song* MusicStreamingService::findSong(const string& songId) const {
    auto it = find_if(songs.begin(), songs.end(),
        [&songId](const Song* song) { return song->getSongId() == songId; });
    return it != songs.end() ? *it : nullptr;
}

Playlist* MusicStreamingService::findPlaylist(const string& playlistId) const {
    for (const auto& user : users) {
        for (const auto& playlist : user->getPlaylists()) {
            if (playlist->getPlaylistId() == playlistId) {
                return playlist;
            }
        }
    }
    return nullptr;
}

string MusicStreamingService::generatePlaylistId() {
    return "P" + to_string(playlistIdCounter++);
} 

// ===== Playlist.cpp =====
Playlist::Playlist(string playlistId, string name, string description,
                  bool isPublic)
    : playlistId(playlistId), name(name), description(description),
      isPublic(isPublic) {}

string Playlist::getPlaylistId() const { return playlistId; }
string Playlist::getName() const { return name; }
string Playlist::getDescription() const { return description; }
bool Playlist::getIsPublic() const { return isPublic; }
const vector<Song*>& Playlist::getSongs() const { return songs; }

void Playlist::addSong(Song* song) {
    if (song && song->isActive()) {
        songs.push_back(song);
    }
}

void Playlist::removeSong(Song* song) {
    auto it = find(songs.begin(), songs.end(), song);
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
    cout << "\nPlaylist: " << name << " (ID: " << playlistId << ")" << endl;
    cout << "Description: " << description << endl;
    cout << "Visibility: " << (isPublic ? "Public" : "Private") << endl;
    cout << "Number of Songs: " << songs.size() << endl;
    
    int totalDuration = getTotalDuration();
    int minutes = totalDuration / 60;
    int seconds = totalDuration % 60;
    cout << "Total Duration: " << minutes << ":" 
              << setfill('0') << setw(2) << seconds << endl;
    
    if (!songs.empty()) {
        cout << "\nSongs:" << endl;
        for (const auto& song : songs) {
            cout << "- " << song->getTitle() << " by " << song->getArtist() << endl;
        }
    }
} 

// ===== Song.cpp =====
Song::Song(string songId, string title, string artist,
           string album, Genre genre, int durationSeconds,
           string filePath)
    : songId(songId), title(title), artist(artist), album(album),
      genre(genre), durationSeconds(durationSeconds), filePath(filePath),
      active(true) {}

string Song::getSongId() const { return songId; }
string Song::getTitle() const { return title; }
string Song::getArtist() const { return artist; }
string Song::getAlbum() const { return album; }
Genre Song::getGenre() const { return genre; }
int Song::getDurationSeconds() const { return durationSeconds; }
string Song::getFilePath() const { return filePath; }
bool Song::isActive() const { return active; }

void Song::setActive(bool status) {
    active = status;
}

void Song::displayInfo() const {
    cout << "Song: " << title << " (ID: " << songId << ")" << endl;
    cout << "Artist: " << artist << endl;
    cout << "Album: " << album << endl;
    cout << "Genre: ";
    switch (genre) {
        case Genre::POP: cout << "Pop"; break;
        case Genre::ROCK: cout << "Rock"; break;
        case Genre::JAZZ: cout << "Jazz"; break;
        case Genre::CLASSICAL: cout << "Classical"; break;
        case Genre::HIPHOP: cout << "Hip Hop"; break;
        case Genre::ELECTRONIC: cout << "Electronic"; break;
    }
    cout << endl;
    
    int minutes = durationSeconds / 60;
    int seconds = durationSeconds % 60;
    cout << "Duration: " << minutes << ":" 
              << setfill('0') << setw(2) << seconds << endl;
    cout << "Status: " << (active ? "Active" : "Inactive") << endl;
} 

// ===== User.cpp =====
User::User(string userId, string username, string email,
           UserType type)
    : userId(userId), username(username), email(email), type(type),
      active(true) {}

User::~User() {
    for (auto playlist : playlists) {
        delete playlist;
    }
}

string User::getUserId() const { return userId; }
string User::getUsername() const { return username; }
string User::getEmail() const { return email; }
UserType User::getType() const { return type; }
bool User::isActive() const { return active; }
const vector<Playlist*>& User::getPlaylists() const { return playlists; }

void User::addPlaylist(Playlist* playlist) {
    playlists.push_back(playlist);
}

void User::removePlaylist(Playlist* playlist) {
    auto it = find(playlists.begin(), playlists.end(), playlist);
    if (it != playlists.end()) {
        delete *it;
        playlists.erase(it);
    }
}

void User::upgradeToPremuim() {
    type = UserType::PREMIUM;
}

void User::setActive(bool status) {
    active = status;
}

void User::displayInfo() const {
    cout << "User: " << username << " (ID: " << userId << ")" << endl;
    cout << "Email: " << email << endl;
    cout << "Type: " << (type == UserType::PREMIUM ? "Premium" : "Free") << endl;
    cout << "Status: " << (active ? "Active" : "Inactive") << endl;
    cout << "Number of Playlists: " << playlists.size() << endl;
} 

// ===== MusicStreamingDemo.cpp =====
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
    cout << "Initial catalog:" << endl;
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
    cout << "\nUser Playlists:" << endl;
    service.displayUserPlaylists("U001");
    service.displayUserPlaylists("U002");
    
    // Search functionality
    cout << "\nSearching for 'Beatles':" << endl;
    auto songResults = service.searchSongs("Beatles");
    for (const auto& song : songResults) {
        song->displayInfo();
    }
    
    // Remove song from playlist
    cout << "\nRemoving 'Hey Jude' from Rock Classics playlist..." << endl;
    if (service.removeSongFromPlaylist(playlist1->getPlaylistId(), "S001")) {
        cout << "Song removed successfully" << endl;
        service.displayUserPlaylists("U001");
    }
    
    // Upgrade user to premium
    cout << "\nUpgrading user john_doe to premium..." << endl;
    user1->upgradeToPremuim();
    user1->displayInfo();
    
    return 0;
} 

