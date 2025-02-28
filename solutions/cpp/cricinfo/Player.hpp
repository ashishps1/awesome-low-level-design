#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include "PlayerStats.hpp"

enum class PlayerType {
    BATSMAN,
    BOWLER,
    ALL_ROUNDER
};

class Player {
private:
    std::string playerId;
    std::string name;
    std::string country;
    PlayerType type;
    PlayerStats stats;

public:
    Player(std::string playerId, std::string name, std::string country, PlayerType type);
    
    std::string getPlayerId() const;
    std::string getName() const;
    std::string getCountry() const;
    PlayerType getType() const;
    PlayerStats& getStats();
    
    void updateStats(const PlayerStats& matchStats);
    void displayInfo() const;
};

#endif 