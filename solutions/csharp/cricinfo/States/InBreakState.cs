class InBreakState : IMatchState
{
    public void ProcessBall(Match match, Ball ball)
    {
        Console.WriteLine("ERROR: Cannot process a ball. The match is currently in a break.");
    }

    public void StartNextInnings(Match match)
    {
        Console.WriteLine("Starting the next innings...");
        match.CreateNewInnings();
        match.SetState(new LiveState());
        match.SetCurrentStatus(MatchStatus.LIVE);
    }
}