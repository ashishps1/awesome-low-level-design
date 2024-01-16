# Designing a Cricket Information System

In this article, we're going to explore the object-oriented design and implementation of a cricket information system, similar to Cricinfo, using Java. 

This system will focus on delivering real-time cricket match updates, managing player statistics, and maintaining team information.

## System Requirements

The system needs to:

1. **Manage Match Details:** Provide real-time updates of cricket matches.
2. **Manage Players and Teams:** Store and update information about players and teams.
3. **Track Statistics:** Keep records of player and team statistics.
4. **Schedule Matches:** Organize and update upcoming cricket matches and series.

## Core Use Cases:

1. **Updating Match Details:** Real-time updates of match scores and events.
2. **Managing Player/Team Profiles:** Adding and updating profiles of players and teams.
3. **Viewing Statistics:** Accessing statistical data of players and teams.
4. **Scheduling Matches:** Planning and updating upcoming matches and series.

## Key Classes:
- `CricketSystem` : Central system managing all functionalities.
- `Match`: Represents a cricket match.
- `Player`: Represents a cricket player.
- `Team`: Represents a cricket team.
- `Statistics`: Manages statistical data.

## Java Implementation

### Player Class

Manages player information and statistics.

```java
public class Player {
    private String name;
    private Team team;
    private Statistics stats;

    public Player(String name, Team team) {
        this.name = name;
        this.team = team;
        this.stats = new Statistics();
    }

    public void updateStatistics(int runs, int wickets) {
        stats.updateStats(runs, wickets);
    }

    // Getters and setters...
}
```
### Team Class
Represents a cricket team.
```java
public class Team {
    private String name;
    private List<Player> players;

    public Team(String name) {
        this.name = name;
        this.players = new ArrayList<>();
    }

    public void addPlayer(Player player) {
        players.add(player);
    }

    // Getters and setters...
}
```
### Match Class
Manages cricket match details.
```java
public class Match {
    private Team teamA;
    private Team teamB;
    private MatchStatus status;
    private String location;
    private int teamAScore;
    private int teamBScore;

    public Match(Team teamA, Team teamB, String location) {
        this.teamA = teamA;
        this.teamB = teamB;
        this.location = location;
        this.status = MatchStatus.SCHEDULED;
    }

    public void updateMatchDetails(int teamAScore, int teamBScore, MatchStatus status) {
        this.teamAScore = teamAScore;
        this.teamBScore = teamBScore;
        this.status = status;
    }

    // Getters and setters...
}

enum MatchStatus {
    SCHEDULED, LIVE, COMPLETED
}
```
### Statistics Class
Manages a player's cricket statistics.
```java
public class Statistics {
    private int matchesPlayed;
    private int runs;
    private int wickets;

    public void updateStats(int runsScored, int wicketsTaken) {
        this.matchesPlayed++;
        this.runs += runsScored;
        this.wickets += wicketsTaken;
    }

    // Getters and setters...
}
```
### CricketSystem Class
Main class for the cricket information system.
```java
public class CricketSystem {
    private List<Match> matches;
    private List<Team> teams;

    public CricketSystem() {
        this.matches = new ArrayList<>();
        this.teams = new ArrayList<>();
    }

    public void addMatch(Match match) {
        matches.add(match);
    }

    public void addTeam(Team team) {
        teams.add(team);
    }

    public void updateMatch(String matchId, int teamAScore, int teamBScore, MatchStatus status) {
        // Find the match by matchId and update its details
        // Implementation details...
    }

    // Other necessary methods...
}
```