#include "User.hpp"
#include <iostream>
#include <algorithm>

User::User(std::string userId, std::string email, std::string password)
    : userId(userId), email(email), password(password), profile(nullptr), active(true) {}

User::~User() {
    delete profile;
    for (auto post : posts) {
        delete post;
    }
}

std::string User::getUserId() const { return userId; }
std::string User::getEmail() const { return email; }
Profile* User::getProfile() const { return profile; }
bool User::isActive() const { return active; }
const std::vector<User*>& User::getConnections() const { return connections; }
const std::vector<Post*>& User::getPosts() const { return posts; }

void User::setProfile(Profile* profile) {
    delete this->profile;
    this->profile = profile;
}

void User::addConnection(User* user) {
    if (user && std::find(connections.begin(), connections.end(), user) == connections.end()) {
        connections.push_back(user);
        user->connections.push_back(this);
    }
}

void User::removeConnection(User* user) {
    auto it = std::find(connections.begin(), connections.end(), user);
    if (it != connections.end()) {
        connections.erase(it);
        auto it2 = std::find(user->connections.begin(), user->connections.end(), this);
        if (it2 != user->connections.end()) {
            user->connections.erase(it2);
        }
    }
}

void User::addPost(Post* post) {
    posts.push_back(post);
}

void User::setActive(bool status) {
    active = status;
}

void User::displayInfo() const {
    std::cout << "User ID: " << userId << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Status: " << (active ? "Active" : "Inactive") << std::endl;
    std::cout << "Connections: " << connections.size() << std::endl;
    std::cout << "Posts: " << posts.size() << std::endl;
    if (profile) {
        profile->displayInfo();
    }
} 