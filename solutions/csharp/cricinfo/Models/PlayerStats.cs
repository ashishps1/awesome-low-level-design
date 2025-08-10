class PlayerStats
{
    private int runs;
    private int ballsPlayed;
    private int wickets;

    public PlayerStats()
    {
        runs = 0;
        ballsPlayed = 0;
        wickets = 0;
    }

    public void UpdateRuns(int runScored)
    {
        runs += runScored;
    }

    public void IncrementBallsPlayed()
    {
        ballsPlayed++;
    }

    public void IncrementWickets()
    {
        wickets++;
    }

    public int GetRuns() => runs;
    public int GetBallsPlayed() => ballsPlayed;
    public int GetWickets() => wickets;

    public override string ToString()
    {
        return $"Runs: {runs}, Balls Played: {ballsPlayed}, Wickets: {wickets}";
    }
}