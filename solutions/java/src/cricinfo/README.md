# Cricket Information System (LLD)

## Problem Statement

Design and implement a Cricket Information System similar to CricInfo that provides comprehensive information about cricket matches, teams, players, and live scores. The system should handle real-time updates, match statistics, and user interactions.

---

## Requirements

1. **Match Information Management:**
   - Store and manage cricket match details
   - Track match schedules and results
   - Support real-time score updates
   - Handle match status transitions

2. **Team and Player Management:**
   - Maintain team rosters and player information
   - Track player roles and statistics
   - Support team composition changes

3. **Scorecard Management:**
   - Record detailed match statistics
   - Track innings, overs, and ball-by-ball information
   - Maintain batting and bowling statistics

4. **Search and Retrieval:**
   - Search for matches, teams, and players
   - View detailed match information
   - Access historical data and statistics

5. **System Requirements:**
   - Handle concurrent access
   - Ensure data consistency
   - Support scalability
   - Allow for future extensions

---

## Core Entities

### 1. Match
- **Fields:** String id, String title, String venue, Date startTime, Team team1, Team team2, MatchStatus status, Scorecard scorecard
- **Methods:** updateStatus(), getScorecard(), getMatchDetails()

### 2. Team
- **Fields:** String id, String name, List<Player> players
- **Methods:** addPlayer(), removePlayer(), getTeamStats()

### 3. Player
- **Fields:** String id, String name, String role
- **Methods:** getPlayerStats(), updateRole()

### 4. Scorecard
- **Fields:** Match match, List<Innings> innings
- **Methods:** addInnings(), updateScore(), getMatchSummary()

### 5. Innings
- **Fields:** String id, Team battingTeam, Team bowlingTeam, List<Over> overs
- **Methods:** addOver(), getInningsSummary()

### 6. Over
- **Fields:** int overNumber, List<Ball> balls
- **Methods:** addBall(), getOverSummary()

### 7. Ball
- **Fields:** int ballNumber, Player bowler, Player batsman, String result
- **Methods:** recordResult(), getBallDetails()

### 8. MatchStatus (Enum)
- **Values:** SCHEDULED, IN_PROGRESS, COMPLETED, ABANDONED

---

## Services

### 1. MatchService (Singleton)
- **Methods:** 
  - addMatch(Match match)
  - getMatch(String id)
  - updateMatchStatus(String id, MatchStatus status)
  - searchMatches(String query)

### 2. ScorecardService (Singleton)
- **Methods:**
  - createScorecard(Match match)
  - updateScorecard(String matchId, Scorecard scorecard)
  - getScorecard(String matchId)
  - addInnings(String matchId, Innings innings)

### 3. CricinfoSystem
- **Methods:**
  - getMatchDetails(String matchId)
  - getTeamDetails(String teamId)
  - getPlayerDetails(String playerId)
  - search(String query)

---

## Example Usage

```java
CricinfoSystem system = CricinfoSystem.getInstance();

// Create a new match
Match match = system.createMatch("IND vs AUS", "Melbourne Cricket Ground", new Date());

// Update match status
system.updateMatchStatus(match.getId(), MatchStatus.IN_PROGRESS);

// Record a ball
system.recordBall(match.getId(), 1, 1, "FOUR");

// Get match details
MatchDetails details = system.getMatchDetails(match.getId());
```

---

## Demo

See the demo class for a sample usage and simulation of the cricket information system.

---

## Extending the Framework

- **Add user authentication:** Support for user accounts and preferences
- **Add commentary system:** Real-time match commentary
- **Add statistics engine:** Advanced player and team statistics
- **Add notification system:** Match updates and alerts
- **Add social features:** User comments and discussions

---

## Design Patterns Used

- **Singleton Pattern:** For service classes (MatchService, ScorecardService)
- **Factory Pattern:** For creating matches and scorecards
- **Observer Pattern:** For real-time updates and notifications
- **Strategy Pattern:** For different types of match formats

---