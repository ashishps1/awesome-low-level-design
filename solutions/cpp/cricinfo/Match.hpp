#ifndef MATCH_HPP
#define MATCH_HPP

#include <string>
#include <vector>
#include "Team.hpp"
#include "PlayerStats.hpp"
#include <map>

class Match {
private:
    std::string matchId;
    Team* team1;
    Team* team2;
    std::string venue;
    std::string date;
    std::string matchType;
    Team* winner;
    std::map<std::string, PlayerStats> playerPerformances;

public:
    Match(std::string matchId, Team* team1, Team* team2, 
          std::string venue, std::string date, std::string matchType);
    
    std::string getMatchId() const;
    Team* getTeam1() const;
    Team* getTeam2() const;
    std::string getVenue() const;
    std::string getDate() const;
    std::string getMatchType() const;
    Team* getWinner() const;
    
    void setWinner(Team* team);
    void addPlayerPerformance(const std::string& playerId, const PlayerStats& stats);
    void updateTeamStats();
    void displayInfo() const;
};

#endif 