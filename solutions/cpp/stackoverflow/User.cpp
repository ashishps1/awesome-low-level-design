#include "User.hpp"
#include <iostream>

User::User(std::string userId, std::string username, std::string email)
    : userId(userId), username(username), email(email), reputation(1), active(true) {}

std::string User::getUserId() const { return userId; }
std::string User::getUsername() const { return username; }
std::string User::getEmail() const { return email; }
int User::getReputation() const { return reputation; }
const std::vector<std::string>& User::getBadges() const { return badges; }
bool User::isActive() const { return active; }

void User::updateReputation(int points) {
    reputation += points;
}

void User::addBadge(const std::string& badge) {
    badges.push_back(badge);
}

void User::setActive(bool status) {
    active = status;
}

void User::displayInfo() const {
    std::cout << "User: " << username << " (ID: " << userId << ")" << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Reputation: " << reputation << std::endl;
    std::cout << "Status: " << (active ? "Active" : "Inactive") << std::endl;
    
    if (!badges.empty()) {
        std::cout << "Badges:" << std::endl;
        for (const auto& badge : badges) {
            std::cout << "- " << badge << std::endl;
        }
    }
} 