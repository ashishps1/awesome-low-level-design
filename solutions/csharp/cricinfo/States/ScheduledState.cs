class ScheduledState : IMatchState
{
    public void ProcessBall(Match match, Ball ball)
    {
        Console.WriteLine("ERROR: Cannot process a ball for a match that has not started.");
    }

    public void StartNextInnings(Match match)
    {
        Console.WriteLine("ERROR: Cannot start the next innings from the current state.");
    }
}