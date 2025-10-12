class CommentaryDisplay : IMatchObserver
{
    public void Update(Match match, Ball lastBall)
    {
        if (match.GetCurrentStatus() == MatchStatus.FINISHED)
        {
            Console.WriteLine("[COMMENTARY]: Match has finished!");
        }
        else if (match.GetCurrentStatus() == MatchStatus.IN_BREAK)
        {
            Console.WriteLine("[COMMENTARY]: Inning has ended!");
        }
        else if (lastBall != null)
        {
            Console.WriteLine($"[COMMENTARY]: {lastBall.GetCommentary()}");
        }
    }
}