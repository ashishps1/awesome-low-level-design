package tictactoe;

public class Game {
    private final Board board;
    private final Player[] players;
    private int currentPlayerIndex;
    private GameStatus status;

    public Game(Player player1, Player player2, int size) {
        this.board = new Board(size);
        this.players = new Player[]{player1, player2};
        this.status = GameStatus.IN_PROGRESS;
    }

    public synchronized boolean playMove(int row, int col) {
        if (status != GameStatus.IN_PROGRESS) {
            throw new IllegalStateException("Game already finished.");
        }

        if (!board.isValidMove(row, col)) {
            throw new IllegalArgumentException("Invalid move.");
        }

        Player current = players[currentPlayerIndex];
        board.placeMove(row, col, current.getSymbol());

        if (board.checkWin(current.getSymbol())) {
            status = GameStatus.WIN;
            System.out.println(current.getName() + " wins!");
        } else if (board.isFull()) {
            status = GameStatus.DRAW;
            System.out.println("Game ended in a draw.");
        } else {
            currentPlayerIndex = 1 - currentPlayerIndex;
        }

        return true;
    }

    public synchronized void reset() {
        board.reset();
        currentPlayerIndex = 0;
        status = GameStatus.IN_PROGRESS;
    }

    public GameStatus getStatus() {
        return status;
    }

    public void printBoard() {
        board.print();
    }
}
