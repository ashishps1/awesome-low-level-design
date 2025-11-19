package tictactoe.models;

import tictactoe.enums.Symbol;
import tictactoe.exceptions.InvalidMoveException;

public class Board {
    private final int size;
    private int movesCount;                // FIX 1: must NOT be final, because we need to increment it
    private final Cell[][] board;

    public Board(int size) {
        this.size = size;
        this.board = new Cell[size][size];
        movesCount = 0;                   // initialize move counter
        initializeBoard();
    }

    private void initializeBoard() {
        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {
                board[row][col] = new Cell();  
            }
        }
    }

    // FIX 2: movesCount MUST be incremented inside the move method
    public boolean placeSymbol(int row, int col, Symbol symbol) {
        // Validate bounds
        if (row < 0 || row >= size || col < 0 || col >= size) {
            throw new InvalidMoveException("Invalid position: out of bounds.");
        }

        // Validate that cell is empty
        if (board[row][col].getSymbol() != Symbol.EMPTY) {
            throw new InvalidMoveException("Invalid position: cell is already occupied.");
        }

        // Place the move
        board[row][col].setSymbol(symbol);

        movesCount++;  
        // FIX 2 EXPLANATION:
        // Earlier this was missing!
        // Without this increment, isFull() would NEVER return true.
        // Now it correctly tracks the number of moves.

        return true;
    }

    public Cell getCell(int row, int col) {
        if (row < 0 || row >= size || col < 0 || col >= size) {
            return null;
        }
        return board[row][col];
    }

    public boolean isFull() {
        // FIX 3: This now works correctly because movesCount increments properly
        return movesCount == size * size;
    }

    public void printBoard() {
        System.out.println("-------------");
        for (int i = 0; i < size; i++) {
            System.out.print("| ");
            for (int j = 0; j < size; j++) {
                Symbol symbol = board[i][j].getSymbol();
                System.out.print(symbol.getChar() + " | ");
            }
            System.out.println("\n-------------");
        }
    }

    public int getSize() {
        return size;
    }
}
