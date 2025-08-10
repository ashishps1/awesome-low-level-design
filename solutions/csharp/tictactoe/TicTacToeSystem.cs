class TicTacToeSystem
{
    private static volatile TicTacToeSystem instance;
    private static readonly object lockObject = new object();
    private Game game;
    private readonly Scoreboard scoreboard; // The system now manages a scoreboard

    private TicTacToeSystem()
    {
        scoreboard = new Scoreboard(); // Create the scoreboard on initialization
    }

    public static TicTacToeSystem GetInstance()
    {
        if (instance == null)
        {
            lock (lockObject)
            {
                if (instance == null)
                {
                    instance = new TicTacToeSystem();
                }
            }
        }
        return instance;
    }

    public void CreateGame(Player player1, Player player2)
    {
        game = new Game(player1, player2);
        // Register the scoreboard as an observer for this new game
        game.AddObserver(scoreboard);

        Console.WriteLine("Game started between " + player1.GetName() + " (X) and " + player2.GetName() + " (O).");
    }

    public void MakeMove(Player player, int row, int col)
    {
        if (game == null)
        {
            Console.WriteLine("No game in progress. Please create a game first.");
            return;
        }

        try
        {
            Console.WriteLine(player.GetName() + " plays at (" + row + ", " + col + ")");
            game.MakeMove(player, row, col);
            PrintBoard();
            Console.WriteLine("Game Status: " + game.GetStatus());
            if (game.GetWinner() != null)
            {
                Console.WriteLine("Winner: " + game.GetWinner().GetName());
            }
        }
        catch (InvalidMoveException e)
        {
            Console.WriteLine("Error: " + e.Message);
        }
    }

    public void PrintBoard()
    {
        game.GetBoard().PrintBoard();
    }

    public void PrintScoreBoard()
    {
        scoreboard.PrintScores();
    }
}