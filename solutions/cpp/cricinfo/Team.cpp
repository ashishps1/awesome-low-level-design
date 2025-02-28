#include "Team.hpp"
#include <iostream>
#include <algorithm>

Team::Team(std::string teamId, std::string name, std::string country)
    : teamId(teamId), name(name), country(country), matchesWon(0), matchesLost(0) {}

std::string Team::getTeamId() const { return teamId; }
std::string Team::getName() const { return name; }
std::string Team::getCountry() const { return country; }
int Team::getMatchesWon() const { return matchesWon; }
int Team::getMatchesLost() const { return matchesLost; }

void Team::addPlayer(Player* player) {
    if (player && player->getCountry() == country) {
        players.push_back(player);
    }
}

void Team::removePlayer(Player* player) {
    auto it = std::find(players.begin(), players.end(), player);
    if (it != players.end()) {
        players.erase(it);
    }
}

Player* Team::findPlayer(const std::string& playerId) const {
    for (auto player : players) {
        if (player->getPlayerId() == playerId) return player;
    }
    return nullptr;
}

void Team::incrementWins() { matchesWon++; }
void Team::incrementLosses() { matchesLost++; }

void Team::displayInfo() const {
    std::cout << "\nTeam: " << name << " (ID: " << teamId << ")" << std::endl;
    std::cout << "Country: " << country << std::endl;
    std::cout << "Matches Won: " << matchesWon << std::endl;
    std::cout << "Matches Lost: " << matchesLost << std::endl;
}

void Team::displayPlayers() const {
    std::cout << "\nPlayers in " << name << ":" << std::endl;
    for (const auto& player : players) {
        player->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
} 