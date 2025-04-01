#include "Player.hpp"
#include <iostream>
#include <iomanip>

Player::Player(std::string playerId, std::string name, std::string country, PlayerType type)
    : playerId(playerId), name(name), country(country), type(type) {}

std::string Player::getPlayerId() const { return playerId; }
std::string Player::getName() const { return name; }
std::string Player::getCountry() const { return country; }
PlayerType Player::getType() const { return type; }
PlayerStats& Player::getStats() { return stats; }

void Player::updateStats(const PlayerStats& matchStats) {
    stats.runsScored += matchStats.runsScored;
    stats.ballsFaced += matchStats.ballsFaced;
    stats.wicketsTaken += matchStats.wicketsTaken;
    stats.ballsBowled += matchStats.ballsBowled;
    stats.matchesPlayed++;
}

void Player::displayInfo() const {
    std::cout << "Player: " << name << " (ID: " << playerId << ")" << std::endl;
    std::cout << "Country: " << country << std::endl;
    std::cout << "Type: ";
    switch (type) {
        case PlayerType::BATSMAN: std::cout << "Batsman"; break;
        case PlayerType::BOWLER: std::cout << "Bowler"; break;
        case PlayerType::ALL_ROUNDER: std::cout << "All-Rounder"; break;
    }
    std::cout << std::endl;
    
    std::cout << "Stats:" << std::endl;
    std::cout << "Matches: " << stats.matchesPlayed << std::endl;
    std::cout << "Runs: " << stats.runsScored << std::endl;
    std::cout << "Balls Faced: " << stats.ballsFaced << std::endl;
    if (stats.ballsFaced > 0) {
        double strikeRate = (static_cast<double>(stats.runsScored) / stats.ballsFaced) * 100;
        std::cout << "Strike Rate: " << std::fixed << std::setprecision(2) << strikeRate << std::endl;
    }
    std::cout << "Wickets: " << stats.wicketsTaken << std::endl;
    std::cout << "Balls Bowled: " << stats.ballsBowled << std::endl;
} 