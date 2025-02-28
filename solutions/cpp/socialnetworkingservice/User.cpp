#include "User.hpp"
#include <iostream>

User::User(std::string userId, std::string username, std::string email)
    : userId(userId), username(username), email(email), active(true) {}

std::string User::getUserId() const { return userId; }
std::string User::getUsername() const { return username; }
std::string User::getEmail() const { return email; }
const std::set<std::string>& User::getFriends() const { return friends; }
bool User::isActive() const { return active; }

void User::addFriend(const std::string& friendId) {
    friends.insert(friendId);
}

void User::removeFriend(const std::string& friendId) {
    friends.erase(friendId);
}

void User::setActive(bool status) {
    active = status;
}

void User::displayInfo() const {
    std::cout << "User: " << username << " (ID: " << userId << ")" << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Status: " << (active ? "Active" : "Inactive") << std::endl;
    std::cout << "Friends: " << friends.size() << std::endl;
} 