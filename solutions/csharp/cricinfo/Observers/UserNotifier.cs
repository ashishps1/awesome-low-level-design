class UserNotifier : IMatchObserver
{
    public void Update(Match match, Ball lastBall)
    {
        if (match.GetCurrentStatus() == MatchStatus.FINISHED)
        {
            Console.WriteLine("[NOTIFICATION]: Match has finished!");
        }
        else if (match.GetCurrentStatus() == MatchStatus.IN_BREAK)
        {
            Console.WriteLine("[NOTIFICATION]: Inning has ended!");
        }
        else if (lastBall != null && lastBall.IsWicket())
        {
            Console.WriteLine("[NOTIFICATION]: Wicket! A player is out.");
        }
        else if (lastBall != null && lastBall.IsBoundary())
        {
            Console.WriteLine($"[NOTIFICATION]: It's a boundary! {lastBall.GetRunsScored()} runs.");
        }
    }
}