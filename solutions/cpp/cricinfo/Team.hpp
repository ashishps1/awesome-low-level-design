#ifndef TEAM_HPP
#define TEAM_HPP

#include <string>
#include <vector>
#include "Player.hpp"

class Team {
private:
    std::string teamId;
    std::string name;
    std::string country;
    std::vector<Player*> players;
    int matchesWon;
    int matchesLost;

public:
    Team(std::string teamId, std::string name, std::string country);
    
    std::string getTeamId() const;
    std::string getName() const;
    std::string getCountry() const;
    int getMatchesWon() const;
    int getMatchesLost() const;
    
    void addPlayer(Player* player);
    void removePlayer(Player* player);
    Player* findPlayer(const std::string& playerId) const;
    void incrementWins();
    void incrementLosses();
    void displayInfo() const;
    void displayPlayers() const;
};

#endif 