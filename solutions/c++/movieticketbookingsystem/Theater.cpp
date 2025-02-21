#include "Theater.hpp"
#include <iostream>
#include <algorithm>

Theater::Theater(std::string theaterId, std::string name, std::string location,
                int totalSeats)
    : theaterId(theaterId), name(name), location(location),
      totalSeats(totalSeats), active(true) {}

Theater::~Theater() {
    for (auto show : shows) {
        delete show;
    }
}

std::string Theater::getTheaterId() const { return theaterId; }
std::string Theater::getName() const { return name; }
std::string Theater::getLocation() const { return location; }
int Theater::getTotalSeats() const { return totalSeats; }
bool Theater::isActive() const { return active; }
const std::vector<Show*>& Theater::getShows() const { return shows; }

void Theater::addShow(Show* show) {
    shows.push_back(show);
}

void Theater::removeShow(Show* show) {
    auto it = std::find(shows.begin(), shows.end(), show);
    if (it != shows.end()) {
        shows.erase(it);
    }
}

void Theater::setActive(bool status) {
    active = status;
}

void Theater::displayInfo() const {
    std::cout << "Theater: " << name << " (ID: " << theaterId << ")" << std::endl;
    std::cout << "Location: " << location << std::endl;
    std::cout << "Total Seats: " << totalSeats << std::endl;
    std::cout << "Status: " << (active ? "Active" : "Inactive") << std::endl;
    std::cout << "Number of Shows: " << shows.size() << std::endl;
} 