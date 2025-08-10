class FinishedState : IMatchState
{
    public void ProcessBall(Match match, Ball ball)
    {
        Console.WriteLine("ERROR: Cannot process a ball for a finished match.");
    }

    public void StartNextInnings(Match match)
    {
        Console.WriteLine("ERROR: Cannot start the next innings from the current state.");
    }
}