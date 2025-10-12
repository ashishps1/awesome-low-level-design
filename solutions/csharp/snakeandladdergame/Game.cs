class Game
{
    private readonly Board board;
    private readonly Queue<Player> players;
    private readonly Dice dice;
    private GameStatus status;
    private Player winner;

    public Game(Board board, Queue<Player> players, Dice dice)
    {
        this.board = board;
        this.players = new Queue<Player>(players);
        this.dice = dice;
        this.status = GameStatus.NOT_STARTED;
        this.winner = null;
    }

    public void Play()
    {
        if (players.Count < 2)
        {
            Console.WriteLine("Cannot start game. At least 2 players are required.");
            return;
        }

        this.status = GameStatus.RUNNING;
        Console.WriteLine("Game started!");

        while (status == GameStatus.RUNNING)
        {
            Player currentPlayer = players.Dequeue();
            TakeTurn(currentPlayer);

            if (status == GameStatus.RUNNING)
            {
                players.Enqueue(currentPlayer);
            }
        }

        Console.WriteLine("Game Finished!");
        if (winner != null)
        {
            Console.WriteLine("The winner is " + winner.GetName() + "!");
        }
    }

    private void TakeTurn(Player player)
    {
        int roll = dice.Roll();
        Console.WriteLine();
        Console.WriteLine(player.GetName() + "'s turn. Rolled a " + roll + ".");

        int currentPosition = player.GetPosition();
        int nextPosition = currentPosition + roll;

        if (nextPosition > board.GetSize())
        {
            Console.WriteLine("Oops, " + player.GetName() + " needs to land exactly on " + board.GetSize() + ". Turn skipped.");
            return;
        }

        if (nextPosition == board.GetSize())
        {
            player.SetPosition(nextPosition);
            this.winner = player;
            this.status = GameStatus.FINISHED;
            Console.WriteLine("Hooray! " + player.GetName() + " reached the final square " + board.GetSize() + " and won!");
            return;
        }

        int finalPosition = board.GetFinalPosition(nextPosition);

        if (finalPosition > nextPosition) // Ladder
        {
            Console.WriteLine("Wow! " + player.GetName() + " found a ladder 🪜 at " + nextPosition + " and climbed to " + finalPosition + ".");
        }
        else if (finalPosition < nextPosition) // Snake
        {
            Console.WriteLine("Oh no! " + player.GetName() + " was bitten by a snake 🐍 at " + nextPosition + " and slid down to " + finalPosition + ".");
        }
        else
        {
            Console.WriteLine(player.GetName() + " moved from " + currentPosition + " to " + finalPosition + ".");
        }

        player.SetPosition(finalPosition);

        if (roll == 6)
        {
            Console.WriteLine(player.GetName() + " rolled a 6 and gets another turn!");
            TakeTurn(player);
        }
    }
}

class GameBuilder
{
    private Board board;
    private Queue<Player> players;
    private Dice dice;

    public GameBuilder SetBoard(int boardSize, List<BoardEntity> boardEntities)
    {
        this.board = new Board(boardSize, boardEntities);
        return this;
    }

    public GameBuilder SetPlayers(List<string> playerNames)
    {
        this.players = new Queue<Player>();
        foreach (string name in playerNames)
        {
            players.Enqueue(new Player(name));
        }
        return this;
    }

    public GameBuilder SetDice(Dice dice)
    {
        this.dice = dice;
        return this;
    }

    public Game Build()
    {
        if (board == null || players == null || dice == null)
        {
            throw new InvalidOperationException("Board, Players, and Dice must be set.");
        }
        return new Game(board, players, dice);
    }
}