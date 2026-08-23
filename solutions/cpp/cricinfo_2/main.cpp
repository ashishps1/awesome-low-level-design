// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// ----- forward declarations -----
class PlayerStats;
class Player;
class Team;
class Match;
class CricInfoSystem;

// ===== PlayerStats.hpp =====
struct PlayerStats {
    int matchesPlayed;
    int runsScored;
    int ballsFaced;
    int wicketsTaken;
    int ballsBowled;
    
    PlayerStats()
        : matchesPlayed(0), runsScored(0), ballsFaced(0), 
          wicketsTaken(0), ballsBowled(0) {}
};

// ===== Player.hpp =====
enum class PlayerType {
    BATSMAN,
    BOWLER,
    ALL_ROUNDER
};

class Player {
private:
    string playerId;
    string name;
    string country;
    PlayerType type;
    PlayerStats stats;

public:
    Player(string playerId, string name, string country, PlayerType type);
    
    string getPlayerId() const;
    string getName() const;
    string getCountry() const;
    PlayerType getType() const;
    PlayerStats& getStats();
    
    void updateStats(const PlayerStats& matchStats);
    void displayInfo() const;
};

// ===== Team.hpp =====
class Team {
private:
    string teamId;
    string name;
    string country;
    vector<Player*> players;
    int matchesWon;
    int matchesLost;

public:
    Team(string teamId, string name, string country);
    
    string getTeamId() const;
    string getName() const;
    string getCountry() const;
    int getMatchesWon() const;
    int getMatchesLost() const;
    
    void addPlayer(Player* player);
    void removePlayer(Player* player);
    Player* findPlayer(const string& playerId) const;
    void incrementWins();
    void incrementLosses();
    void displayInfo() const;
    void displayPlayers() const;
};

// ===== Match.hpp =====
class Match {
private:
    string matchId;
    Team* team1;
    Team* team2;
    string venue;
    string date;
    string matchType;
    Team* winner;
    map<string, PlayerStats> playerPerformances;

public:
    Match(string matchId, Team* team1, Team* team2, 
          string venue, string date, string matchType);
    
    string getMatchId() const;
    Team* getTeam1() const;
    Team* getTeam2() const;
    string getVenue() const;
    string getDate() const;
    string getMatchType() const;
    Team* getWinner() const;
    
    void setWinner(Team* team);
    void addPlayerPerformance(const string& playerId, const PlayerStats& stats);
    void updateTeamStats();
    void displayInfo() const;
};

// ===== CricInfoSystem.hpp =====
class CricInfoSystem {
private:
    vector<Team*> teams;
    vector<Match*> matches;

public:
    CricInfoSystem();
    ~CricInfoSystem();
    
    void addTeam(Team* team);
    void addMatch(Match* match);
    
    Team* findTeam(const string& teamId) const;
    Match* findMatch(const string& matchId) const;
    
    void displayAllTeams() const;
    void displayAllMatches() const;
    void displayTeamStats(const string& teamId) const;
    void displayPlayerStats(const string& playerId) const;
};

// ===== CricInfoSystem.cpp =====
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

Team* CricInfoSystem::findTeam(const string& teamId) const {
    for (auto team : teams) {
        if (team->getTeamId() == teamId) return team;
    }
    return nullptr;
}

Match* CricInfoSystem::findMatch(const string& matchId) const {
    for (auto match : matches) {
        if (match->getMatchId() == matchId) return match;
    }
    return nullptr;
}

void CricInfoSystem::displayAllTeams() const {
    cout << "\nAll Teams:" << endl;
    for (const auto& team : teams) {
        team->displayInfo();
        cout << "------------------------" << endl;
    }
}

void CricInfoSystem::displayAllMatches() const {
    cout << "\nAll Matches:" << endl;
    for (const auto& match : matches) {
        match->displayInfo();
        cout << "------------------------" << endl;
    }
}

void CricInfoSystem::displayTeamStats(const string& teamId) const {
    Team* team = findTeam(teamId);
    if (team) {
        team->displayInfo();
        team->displayPlayers();
    }
}

void CricInfoSystem::displayPlayerStats(const string& playerId) const {
    for (const auto& team : teams) {
        Player* player = team->findPlayer(playerId);
        if (player) {
            player->displayInfo();
            return;
        }
    }
    cout << "Player not found!" << endl;
} 

// ===== Match.cpp =====
Match::Match(string matchId, Team* team1, Team* team2, 
             string venue, string date, string matchType)
    : matchId(matchId), team1(team1), team2(team2), venue(venue), 
      date(date), matchType(matchType), winner(nullptr) {}

string Match::getMatchId() const { return matchId; }
Team* Match::getTeam1() const { return team1; }
Team* Match::getTeam2() const { return team2; }
string Match::getVenue() const { return venue; }
string Match::getDate() const { return date; }
string Match::getMatchType() const { return matchType; }
Team* Match::getWinner() const { return winner; }

void Match::setWinner(Team* team) {
    winner = team;
}

void Match::addPlayerPerformance(const string& playerId, const PlayerStats& stats) {
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
    cout << "\nMatch Details:" << endl;
    cout << "ID: " << matchId << endl;
    cout << "Type: " << matchType << endl;
    cout << "Venue: " << venue << endl;
    cout << "Date: " << date << endl;
    cout << "Teams: " << team1->getName() << " vs " << team2->getName() << endl;
    if (winner) {
        cout << "Winner: " << winner->getName() << endl;
    }
} 

// ===== Player.cpp =====
Player::Player(string playerId, string name, string country, PlayerType type)
    : playerId(playerId), name(name), country(country), type(type) {}

string Player::getPlayerId() const { return playerId; }
string Player::getName() const { return name; }
string Player::getCountry() const { return country; }
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
    cout << "Player: " << name << " (ID: " << playerId << ")" << endl;
    cout << "Country: " << country << endl;
    cout << "Type: ";
    switch (type) {
        case PlayerType::BATSMAN: cout << "Batsman"; break;
        case PlayerType::BOWLER: cout << "Bowler"; break;
        case PlayerType::ALL_ROUNDER: cout << "All-Rounder"; break;
    }
    cout << endl;
    
    cout << "Stats:" << endl;
    cout << "Matches: " << stats.matchesPlayed << endl;
    cout << "Runs: " << stats.runsScored << endl;
    cout << "Balls Faced: " << stats.ballsFaced << endl;
    if (stats.ballsFaced > 0) {
        double strikeRate = (static_cast<double>(stats.runsScored) / stats.ballsFaced) * 100;
        cout << "Strike Rate: " << fixed << setprecision(2) << strikeRate << endl;
    }
    cout << "Wickets: " << stats.wicketsTaken << endl;
    cout << "Balls Bowled: " << stats.ballsBowled << endl;
} 

// ===== Team.cpp =====
Team::Team(string teamId, string name, string country)
    : teamId(teamId), name(name), country(country), matchesWon(0), matchesLost(0) {}

string Team::getTeamId() const { return teamId; }
string Team::getName() const { return name; }
string Team::getCountry() const { return country; }
int Team::getMatchesWon() const { return matchesWon; }
int Team::getMatchesLost() const { return matchesLost; }

void Team::addPlayer(Player* player) {
    if (player && player->getCountry() == country) {
        players.push_back(player);
    }
}

void Team::removePlayer(Player* player) {
    auto it = find(players.begin(), players.end(), player);
    if (it != players.end()) {
        players.erase(it);
    }
}

Player* Team::findPlayer(const string& playerId) const {
    for (auto player : players) {
        if (player->getPlayerId() == playerId) return player;
    }
    return nullptr;
}

void Team::incrementWins() { matchesWon++; }
void Team::incrementLosses() { matchesLost++; }

void Team::displayInfo() const {
    cout << "\nTeam: " << name << " (ID: " << teamId << ")" << endl;
    cout << "Country: " << country << endl;
    cout << "Matches Won: " << matchesWon << endl;
    cout << "Matches Lost: " << matchesLost << endl;
}

void Team::displayPlayers() const {
    cout << "\nPlayers in " << name << ":" << endl;
    for (const auto& player : players) {
        player->displayInfo();
        cout << "------------------------" << endl;
    }
} 

// ===== CricInfoDemo.cpp =====
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

