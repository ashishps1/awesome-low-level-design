class LiveState : IMatchState
{
    public void ProcessBall(Match match, Ball ball)
    {
        var currentInnings = match.GetCurrentInnings();
        currentInnings.AddBall(ball);
        match.NotifyObservers(ball);
        CheckForMatchEnd(match);
    }

    public void StartNextInnings(Match match)
    {
        Console.WriteLine("ERROR: Cannot start the next innings from the current state.");
    }

    private void CheckForMatchEnd(Match match)
    {
        var currentInnings = match.GetCurrentInnings();
        int inningsCount = match.GetInnings().Count;
        bool isFinalInnings = (inningsCount == match.GetFormatStrategy().GetTotalInnings());

        if (isFinalInnings)
        {
            int targetScore = match.GetInnings()[0].GetScore() + 1;
            if (currentInnings.GetScore() >= targetScore)
            {
                int wicketsRemaining = (currentInnings.GetBattingTeam().GetPlayers().Count - 1) - currentInnings.GetWickets();
                DeclareWinner(match, currentInnings.GetBattingTeam(), $"won by {wicketsRemaining} wickets");
                return;
            }
        }

        if (IsInningsOver(match))
        {
            if (isFinalInnings)
            {
                int score1 = match.GetInnings()[0].GetScore();
                int score2 = currentInnings.GetScore();

                if (score1 > score2)
                {
                    DeclareWinner(match, match.GetTeam1(), $"won by {score1 - score2} runs");
                }
                else if (score2 > score1)
                {
                    int wicketsRemaining = (currentInnings.GetBattingTeam().GetPlayers().Count - 1) - currentInnings.GetWickets();
                    DeclareWinner(match, currentInnings.GetBattingTeam(), $"won by {wicketsRemaining} wickets");
                }
                else
                {
                    DeclareWinner(match, null, "Match Tied");
                }
            }
            else
            {
                Console.WriteLine("End of the innings!");
                match.SetState(new InBreakState());
                match.SetCurrentStatus(MatchStatus.IN_BREAK);
                match.NotifyObservers(null);
            }
        }
    }

    private void DeclareWinner(Match match, Team winningTeam, string message)
    {
        Console.WriteLine("MATCH FINISHED!");
        match.SetWinner(winningTeam);
        string resultMessage = winningTeam != null ? $"{winningTeam.GetName()} {message}" : message;
        match.SetResultMessage(resultMessage);

        match.SetState(new FinishedState());
        match.SetCurrentStatus(MatchStatus.FINISHED);
        match.NotifyObservers(null);
    }

    private bool IsInningsOver(Match match)
    {
        var currentInnings = match.GetCurrentInnings();
        bool allOut = currentInnings.GetWickets() >= currentInnings.GetBattingTeam().GetPlayers().Count - 1;
        bool oversFinished = (int)currentInnings.GetOvers() >= match.GetFormatStrategy().GetTotalOvers();
        return allOut || oversFinished;
    }
}