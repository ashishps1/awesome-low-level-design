#include "User.hpp"
#include <iostream>
#include <algorithm>

User::User(std::string userId, std::string username, std::string email)
    : userId(userId), username(username), email(email), active(true) {}

std::string User::getUserId() const { return userId; }
std::string User::getUsername() const { return username; }
std::string User::getEmail() const { return email; }
const std::vector<std::string>& User::getAssignedTasks() const { return assignedTasks; }
bool User::isActive() const { return active; }

void User::addTask(const std::string& taskId) {
    if (std::find(assignedTasks.begin(), assignedTasks.end(), taskId) == assignedTasks.end()) {
        assignedTasks.push_back(taskId);
    }
}

void User::removeTask(const std::string& taskId) {
    auto it = std::find(assignedTasks.begin(), assignedTasks.end(), taskId);
    if (it != assignedTasks.end()) {
        assignedTasks.erase(it);
    }
}

void User::setActive(bool status) {
    active = status;
}

void User::displayInfo() const {
    std::cout << "User: " << username << " (ID: " << userId << ")" << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Status: " << (active ? "Active" : "Inactive") << std::endl;
    std::cout << "Assigned Tasks: " << assignedTasks.size() << std::endl;
} 