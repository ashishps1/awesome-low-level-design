package tictactoe;

import tictactoe.exceptions.InvalidMoveException;
import tictactoe.models.Player;
import tictactoe.observer.Scoreboard;

public class TicTacToeSystem {
    private static volatile TicTacToeSystem instance;
    private Game game;
    private final Scoreboard scoreboard; // The system now manages a scoreboard

    private TicTacToeSystem() {
        this.scoreboard = new Scoreboard(); // Create the scoreboard on initialization
    }

    public static synchronized TicTacToeSystem getInstance() {
        if (instance == null) {
            instance = new TicTacToeSystem();
        }
        return instance;
    }

    public void createGame(Player player1, Player player2) {
        this.game = new Game(player1, player2);
        // Register the scoreboard as an observer for this new game
        this.game.addObserver(this.scoreboard);

        System.out.printf("Game started between %s (X) and %s (O).%n", player1.getName(), player2.getName());
    }

    public void makeMove(Player player, int row, int col) {
        if (game == null) {
            System.out.println("No game in progress. Please create a game first.");
            return;
        }
        try {
            System.out.printf("%s plays at (%d, %d)%n", player.getName(), row, col);
            game.makeMove(player, row, col);
            printBoard();
            System.out.println("Game Status: " + game.getStatus());
            if (game.getWinner() != null) {
                System.out.println("Winner: " + game.getWinner().getName());
            }
        } catch (InvalidMoveException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    public void printBoard() {
        game.getBoard().printBoard();
    }

    public void printScoreBoard() {
        scoreboard.printScores();
    }
}
