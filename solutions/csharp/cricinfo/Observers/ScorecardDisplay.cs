class ScorecardDisplay : IMatchObserver
{
    public void Update(Match match, Ball lastBall)
    {
        if (match.GetCurrentStatus() == MatchStatus.FINISHED)
        {
            Console.WriteLine("\n--- MATCH RESULT ---");
            Console.WriteLine(match.GetResultMessage().ToUpper());
            Console.WriteLine("--------------------");

            Console.WriteLine("Player Stats:");
            int counter = 1;
            foreach (var inning in match.GetInnings())
            {
                Console.WriteLine($"Inning {counter++}");
                inning.PrintPlayerStats();
            }
        }
        else if (match.GetCurrentStatus() == MatchStatus.IN_BREAK)
        {
            Console.WriteLine("\n--- END OF INNINGS ---");
            var lastInnings = match.GetInnings().Last();
            Console.WriteLine($"Final Score: {lastInnings.GetBattingTeam().GetName()}: " +
                             $"{lastInnings.GetScore()}/{lastInnings.GetWickets()} " +
                             $"(Overs: {lastInnings.GetOvers():F1})");
            Console.WriteLine("------------------------");
        }
        else
        {
            Console.WriteLine("\n--- SCORECARD UPDATE ---");
            var currentInnings = match.GetCurrentInnings();
            Console.WriteLine($"{currentInnings.GetBattingTeam().GetName()}: " +
                             $"{currentInnings.GetScore()}/{currentInnings.GetWickets()} " +
                             $"(Overs: {currentInnings.GetOvers():F1})");
            Console.WriteLine("------------------------");
        }
    }
}