#include "CricInfoSystem.hpp"
#include <iostream>

int main() {
    CricInfoSystem system;
    
    // Create teams
    Team* team1 = new Team("IND", "India", "India");
    Team* team2 = new Team("AUS", "Australia", "Australia");
    
    // Create players
    Player* player1 = new Player("VK18", "Virat Kohli", "India", PlayerType::BATSMAN);
    Player* player2 = new Player("RS45", "Rohit Sharma", "India", PlayerType::BATSMAN);
    Player* player3 = new Player("SPD23", "Steve Smith", "Australia", PlayerType::BATSMAN);
    Player* player4 = new Player("PCU31", "Pat Cummins", "Australia", PlayerType::BOWLER);
    
    // Add players to teams
    team1->addPlayer(player1);
    team1->addPlayer(player2);
    team2->addPlayer(player3);
    team2->addPlayer(player4);
    
    // Add teams to system
    system.addTeam(team1);
    system.addTeam(team2);
    
    // Create a match
    Match* match1 = new Match("M001", team1, team2, "MCG", "2024-01-01", "Test");
    
    // Add player performances
    PlayerStats kohliStats;
    kohliStats.runsScored = 100;
    kohliStats.ballsFaced = 150;
    match1->addPlayerPerformance("VK18", kohliStats);
    
    PlayerStats cumminsStats;
    cumminsStats.wicketsTaken = 3;
    cumminsStats.ballsBowled = 120;
    match1->addPlayerPerformance("PCU31", cumminsStats);
    
    // Set match winner
    match1->setWinner(team1);
    team1->incrementWins();
    team2->incrementLosses();
    
    // Update player stats
    match1->updateTeamStats();
    
    // Add match to system
    system.addMatch(match1);
    
    // Display information
    system.displayAllTeams();
    system.displayAllMatches();
    system.displayPlayerStats("VK18");
    
    return 0;
} 