#ifndef CRIC_INFO_SYSTEM_HPP
#define CRIC_INFO_SYSTEM_HPP

#include <vector>
#include "Team.hpp"
#include "Match.hpp"

class CricInfoSystem {
private:
    std::vector<Team*> teams;
    std::vector<Match*> matches;

public:
    CricInfoSystem();
    ~CricInfoSystem();
    
    void addTeam(Team* team);
    void addMatch(Match* match);
    
    Team* findTeam(const std::string& teamId) const;
    Match* findMatch(const std::string& matchId) const;
    
    void displayAllTeams() const;
    void displayAllMatches() const;
    void displayTeamStats(const std::string& teamId) const;
    void displayPlayerStats(const std::string& playerId) const;
};

#endif 