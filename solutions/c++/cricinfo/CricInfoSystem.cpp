#include "CricInfoSystem.hpp"
#include <iostream>

CricInfoSystem::CricInfoSystem() {}

CricInfoSystem::~CricInfoSystem() {
    for (auto team : teams) delete team;
    for (auto match : matches) delete match;
}

void CricInfoSystem::addTeam(Team* team) {
    teams.push_back(team);
}

void CricInfoSystem::addMatch(Match* match) {
    matches.push_back(match);
}

Team* CricInfoSystem::findTeam(const std::string& teamId) const {
    for (auto team : teams) {
        if (team->getTeamId() == teamId) return team;
    }
    return nullptr;
}

Match* CricInfoSystem::findMatch(const std::string& matchId) const {
    for (auto match : matches) {
        if (match->getMatchId() == matchId) return match;
    }
    return nullptr;
}

void CricInfoSystem::displayAllTeams() const {
    std::cout << "\nAll Teams:" << std::endl;
    for (const auto& team : teams) {
        team->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void CricInfoSystem::displayAllMatches() const {
    std::cout << "\nAll Matches:" << std::endl;
    for (const auto& match : matches) {
        match->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void CricInfoSystem::displayTeamStats(const std::string& teamId) const {
    Team* team = findTeam(teamId);
    if (team) {
        team->displayInfo();
        team->displayPlayers();
    }
}

void CricInfoSystem::displayPlayerStats(const std::string& playerId) const {
    for (const auto& team : teams) {
        Player* player = team->findPlayer(playerId);
        if (player) {
            player->displayInfo();
            return;
        }
    }
    std::cout << "Player not found!" << std::endl;
} 