package cricinfo.entity;

public class PlayerStats {
    private int runs;
    private int ballsPlayed;
    private int wickets;

    public PlayerStats() {
        runs = 0;
        wickets = 0;
    }

    public void updateRuns(int runScored) {
        runs += runScored;
    }

    public void incrementBallsPlayed() {
        ballsPlayed += 1;
    }

    public void incrementWickets() {
        wickets += 1;
    }

    public int getRuns() { return runs; }
    public int getWickets() { return wickets; }
    public int getBallsPlayed() { return ballsPlayed; }

    @Override
    public String toString() {
        return "Runs: " + runs + ", Balls Played: " + ballsPlayed + ", Wickets: " + wickets;
    }
 }
