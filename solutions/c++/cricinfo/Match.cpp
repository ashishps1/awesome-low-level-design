#include "Match.hpp"
#include <iostream>

Match::Match(std::string matchId, Team* team1, Team* team2, 
             std::string venue, std::string date, std::string matchType)
    : matchId(matchId), team1(team1), team2(team2), venue(venue), 
      date(date), matchType(matchType), winner(nullptr) {}

std::string Match::getMatchId() const { return matchId; }
Team* Match::getTeam1() const { return team1; }
Team* Match::getTeam2() const { return team2; }
std::string Match::getVenue() const { return venue; }
std::string Match::getDate() const { return date; }
std::string Match::getMatchType() const { return matchType; }
Team* Match::getWinner() const { return winner; }

void Match::setWinner(Team* team) {
    winner = team;
}

void Match::addPlayerPerformance(const std::string& playerId, const PlayerStats& stats) {
    playerPerformances[playerId] = stats;
}

void Match::updateTeamStats() {
    for (const auto& performance : playerPerformances) {
        Player* player = team1->findPlayer(performance.first);
        if (!player) {
            player = team2->findPlayer(performance.first);
        }
        if (player) {
            player->updateStats(performance.second);
        }
    }
}

void Match::displayInfo() const {
    std::cout << "\nMatch Details:" << std::endl;
    std::cout << "ID: " << matchId << std::endl;
    std::cout << "Type: " << matchType << std::endl;
    std::cout << "Venue: " << venue << std::endl;
    std::cout << "Date: " << date << std::endl;
    std::cout << "Teams: " << team1->getName() << " vs " << team2->getName() << std::endl;
    if (winner) {
        std::cout << "Winner: " << winner->getName() << std::endl;
    }
} 