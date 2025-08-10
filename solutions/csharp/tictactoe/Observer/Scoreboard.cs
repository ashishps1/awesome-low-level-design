using System.Collections.Concurrent;

class Scoreboard : IGameObserver
{
    private readonly ConcurrentDictionary<string, int> scores;

    public Scoreboard()
    {
        scores = new ConcurrentDictionary<string, int>();
    }

    public void Update(Game game)
    {
        // The scoreboard only cares about finished games with a winner
        if (game.GetWinner() != null)
        {
            string winnerName = game.GetWinner().GetName();
            scores.AddOrUpdate(winnerName, 1, (key, value) => value + 1);
            Console.WriteLine("[Scoreboard] " + winnerName + " wins! Their new score is " + scores[winnerName] + ".");
        }
    }

    public void PrintScores()
    {
        Console.WriteLine("\n--- Overall Scoreboard ---");
        if (scores.IsEmpty)
        {
            Console.WriteLine("No games with a winner have been played yet.");
            return;
        }

        foreach (var kvp in scores)
        {
            Console.WriteLine("Player: " + kvp.Key + " | Wins: " + kvp.Value);
        }
        Console.WriteLine("--------------------------\n");
    }
}