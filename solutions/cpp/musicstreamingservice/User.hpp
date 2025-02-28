#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <vector>
#include "Playlist.hpp"

enum class UserType {
    FREE,
    PREMIUM
};

class User {
private:
    std::string userId;
    std::string username;
    std::string email;
    UserType type;
    std::vector<Playlist*> playlists;
    bool active;

public:
    User(std::string userId, std::string username, std::string email,
         UserType type = UserType::FREE);
    ~User();
    
    std::string getUserId() const;
    std::string getUsername() const;
    std::string getEmail() const;
    UserType getType() const;
    bool isActive() const;
    const std::vector<Playlist*>& getPlaylists() const;
    
    void addPlaylist(Playlist* playlist);
    void removePlaylist(Playlist* playlist);
    void upgradeToPremuim();
    void setActive(bool status);
    void displayInfo() const;
};

#endif 