#ifndef PLAYER_STATS_HPP
#define PLAYER_STATS_HPP

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

#endif 