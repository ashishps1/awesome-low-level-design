#include "User.hpp"
#include <iostream>
#include <algorithm>

User::User(std::string userId, std::string username, std::string email,
           UserType type)
    : userId(userId), username(username), email(email), type(type),
      active(true) {}

User::~User() {
    for (auto playlist : playlists) {
        delete playlist;
    }
}

std::string User::getUserId() const { return userId; }
std::string User::getUsername() const { return username; }
std::string User::getEmail() const { return email; }
UserType User::getType() const { return type; }
bool User::isActive() const { return active; }
const std::vector<Playlist*>& User::getPlaylists() const { return playlists; }

void User::addPlaylist(Playlist* playlist) {
    playlists.push_back(playlist);
}

void User::removePlaylist(Playlist* playlist) {
    auto it = std::find(playlists.begin(), playlists.end(), playlist);
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
    std::cout << "User: " << username << " (ID: " << userId << ")" << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Type: " << (type == UserType::PREMIUM ? "Premium" : "Free") << std::endl;
    std::cout << "Status: " << (active ? "Active" : "Inactive") << std::endl;
    std::cout << "Number of Playlists: " << playlists.size() << std::endl;
} 