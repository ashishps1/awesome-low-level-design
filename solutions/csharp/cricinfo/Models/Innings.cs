class Innings
{
    private readonly Team battingTeam;
    private readonly Team bowlingTeam;
    private int score;
    private int wickets;
    private readonly List<Ball> balls;
    private readonly Dictionary<Player, PlayerStats> playerStats;

    public Innings(Team batting, Team bowling)
    {
        battingTeam = batting;
        bowlingTeam = bowling;
        score = 0;
        wickets = 0;
        balls = new List<Ball>();
        playerStats = new Dictionary<Player, PlayerStats>();

        foreach (var player in battingTeam.GetPlayers())
        {
            playerStats[player] = new PlayerStats();
        }
        foreach (var player in bowlingTeam.GetPlayers())
        {
            playerStats[player] = new PlayerStats();
        }
    }

    public void AddBall(Ball ball)
    {
        balls.Add(ball);
        int runsScored = ball.GetRunsScored();
        score += runsScored;

        if (ball.GetExtraType() == ExtraType.WIDE || ball.GetExtraType() == ExtraType.NO_BALL)
        {
            score += 1;
        }
        else
        {
            ball.GetFacedBy().GetStats().UpdateRuns(runsScored);
            ball.GetFacedBy().GetStats().IncrementBallsPlayed();
            playerStats[ball.GetFacedBy()].UpdateRuns(runsScored);
            playerStats[ball.GetFacedBy()].IncrementBallsPlayed();
        }

        if (ball.IsWicket())
        {
            wickets++;
            ball.GetBowledBy().GetStats().IncrementWickets();
            playerStats[ball.GetBowledBy()].IncrementWickets();
        }
    }

    public void PrintPlayerStats()
    {
        foreach (var entry in playerStats)
        {
            var player = entry.Key;
            var stats = entry.Value;

            if (stats.GetBallsPlayed() > 0 || stats.GetWickets() > 0)
            {
                Console.WriteLine($"Player: {player.GetName()} - Stats: {stats}");
            }
        }
    }

    public double GetOvers()
    {
        int validBalls = balls.Count(b => b.GetExtraType() != ExtraType.WIDE && b.GetExtraType() != ExtraType.NO_BALL);

        int completedOvers = validBalls / 6;
        int ballsInCurrentOver = validBalls % 6;

        return completedOvers + (ballsInCurrentOver / 10.0);
    }

    public Team GetBattingTeam() => battingTeam;
    public Team GetBowlingTeam() => bowlingTeam;
    public int GetScore() => score;
    public int GetWickets() => wickets;
    public List<Ball> GetBalls() => balls;
}