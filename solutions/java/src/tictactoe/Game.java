package tictactoe;

import tictactoe.enums.GameStatus;
import tictactoe.models.Board;
import tictactoe.models.Player;
import tictactoe.observer.GameSubject;
import tictactoe.state.GameState;
import tictactoe.state.InProgressState;
import tictactoe.strategy.ColumnWinningStrategy;
import tictactoe.strategy.DiagonalWinningStrategy;
import tictactoe.strategy.RowWinningStrategy;
import tictactoe.strategy.WinningStrategy;

import java.util.List;

public class Game extends GameSubject {
    private final Board board;
    private final Player player1;
    private final Player player2;
    private Player currentPlayer;
    private Player winner;
    private GameStatus status;
    private GameState state;
    private final List<WinningStrategy> winningStrategies;

    public Game(Player player1, Player player2) {
        this.board = new Board(3);
        this.player1 = player1;
        this.player2 = player2;
        this.currentPlayer = player1; // Player 1 starts
        this.status = GameStatus.IN_PROGRESS;
        this.state = new InProgressState();
        this.winningStrategies = List.of(
                new RowWinningStrategy(),
                new ColumnWinningStrategy(),
                new DiagonalWinningStrategy()
        );
    }

    public void makeMove(Player player, int row, int col) {
        state.handleMove(this, player, row, col);
    }

    public boolean checkWinner(Player player) {
        for (WinningStrategy strategy : winningStrategies) {
            if (strategy.checkWinner(board, player)) {
                return true;
            }
        }
        return false;
    }

    public void switchPlayer() {
        this.currentPlayer = (currentPlayer == player1) ? player2 : player1;
    }

    public Board getBoard() { return board; }
    public Player getCurrentPlayer() { return currentPlayer; }
    public Player getWinner() { return winner; }
    public void setWinner(Player winner) { this.winner = winner; }
    public GameStatus getStatus() { return status; }
    public void setState(GameState state) { this.state = state; }
    public void setStatus(GameStatus status) {
        this.status = status;
        // Notify observers when the status changes to a finished state
        if (status != GameStatus.IN_PROGRESS) {
            notifyObservers();
        }
    }
}
