using System;

class Game : GameSubject
{
    private readonly Board board;
    private readonly Player player1;
    private readonly Player player2;
    private Player currentPlayer;
    private Player winner;
    private GameStatus status;
    private IGameState state;
    private readonly List<IWinningStrategy> winningStrategies;

    public Game(Player player1, Player player2)
    {
        board = new Board(3);
        this.player1 = player1;
        this.player2 = player2;
        currentPlayer = player1; // Player 1 starts
        winner = null;
        status = GameStatus.IN_PROGRESS;
        state = new InProgressState();
        winningStrategies = new List<IWinningStrategy>
        {
            new RowWinningStrategy(),
            new ColumnWinningStrategy(),
            new DiagonalWinningStrategy()
        };
    }

    public void MakeMove(Player player, int row, int col)
    {
        state.HandleMove(this, player, row, col);
    }

    public bool CheckWinner(Player player)
    {
        foreach (var strategy in winningStrategies)
        {
            if (strategy.CheckWinner(board, player))
            {
                return true;
            }
        }
        return false;
    }

    public void SwitchPlayer()
    {
        if (currentPlayer == player1)
        {
            currentPlayer = player2;
        }
        else
        {
            currentPlayer = player1;
        }        
    }

    public Board GetBoard() => board;
    public Player GetCurrentPlayer() => currentPlayer;
    public Player GetWinner() => winner;
    public void SetWinner(Player winner) => this.winner = winner;
    public GameStatus GetStatus() => status;
    public void SetState(IGameState state) => this.state = state;
    public void SetStatus(GameStatus status)
    {
        this.status = status;
        // Notify observers when the status changes to a finished state
        if (status != GameStatus.IN_PROGRESS)
        {
            NotifyObservers();
        }
    }
}