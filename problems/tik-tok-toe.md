# Designing a Tic Tac Toe Game

This blog post explores the design and implementation of a Tic Tac Toe game using object-oriented principles in Java. 

It's a classic game that provides a great opportunity to apply fundamental OOP concepts.

## System Requirements

The Tic Tac Toe game will:

1. **Handle Player Moves:** Allow two players to alternately place their marks (X or O) on a 3x3 grid.
2. **Check for Win or Draw:** Determine the outcome of the game – a win for one player, a draw, or continuation.
3. **Reset the Game:** Enable starting a new game after one round finishes.

## Core Use Cases

1. **Making a Move:** Players take turns to place their marks on the grid.
2. **Checking Game Status:** After each move, check if the game is won, drawn, or still ongoing.
3. **Resetting the Game:** Clear the board for a new round.

## UML/Class Diagrams

Key Classes:

- `TicTacToe`: Manages the overall game.
- `Board`: Represents the game board.
- `Player`: Enum to represent the players (X and O).

## Java Implementation

### Player Enum
Represents the players in the game.

```java
public enum Player {
    X, O
}
```
### Board Class
```java
public class Board {
    private Player[][] board;
    private final int size = 3;

    public Board() {
        board = new Player[size][size];
    }

    public boolean makeMove(Player player, int row, int col) {
        if (row >= 0 && row < size && col >= 0 && col < size && board[row][col] == null) {
            board[row][col] = player;
            return true;
        }
        return false;
    }

    public Player checkWinner() {
        // Check rows and columns
        for (int i = 0; i < size; i++) {
            if (board[i][0] != null && board[i][0] == board[i][1] && board[i][1] == board[i][2])
                return board[i][0];
            if (board[0][i] != null && board[0][i] == board[1][i] && board[1][i] == board[2][i])
                return board[0][i];
        }

        // Check diagonals
        if (board[0][0] != null && board[0][0] == board[1][1] && board[1][1] == board[2][2])
            return board[0][0];
        if (board[0][2] != null && board[0][2] == board[1][1] && board[1][1] == board[2][0])
            return board[0][2];

        return null;
    }

    public boolean isFull() {
        for (Player[] row : board) {
            for (Player cell : row) {
                if (cell == null) {
                    return false;
                }
            }
        }
        return true;
    }

    public void reset() {
        for (int i = 0; i < size; i++) {
            Arrays.fill(board[i], null);
        }
    }
}
```
### TicTacToe Class
```java
public class TicTacToe {
    private Board board;
    private Player currentPlayer;
    private GameState gameState;

    public TicTacToe() {
        board = new Board();
        currentPlayer = Player.X; // X starts the game
        gameState = GameState.PLAYING;
    }

    public void playMove(int row, int col) {
        if (board.makeMove(currentPlayer, row, col)) {
            Player winner = board.checkWinner();
            if (winner != null) {
                gameState = (winner == Player.X) ? GameState.X_WON : GameState.O_WON;
            } else if (board.isFull()) {
                gameState = GameState.DRAW;
            } else {
                currentPlayer = (currentPlayer == Player.X) ? Player.O : Player.X;
            }
        }
    }

    public void resetGame() {
        board.reset();
        currentPlayer = Player.X;
        gameState = GameState.PLAYING;
    }

    // Getters and other methods...
}
```