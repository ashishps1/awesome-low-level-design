package tictactoe;

import tictactoe.winningstrategy.WinningStrategy;

import java.util.List;

public class Board {
    private final Cell[][] grid;
    private final int movesCount;
    private final int size;
    List<WinningStrategy> winningStrategies;

    public Board(int size, List<WinningStrategy> winningStrategies) {
        this.size = size;
        grid = new Cell[size][size];
        movesCount = 0;
        initializeBoard();
        this.winningStrategies = winningStrategies;
    }

    private void initializeBoard() {
        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {
                grid[row][col] = new Cell();
            }
        }
    }

    public boolean isValidMove(int row, int col) {
        return row >= 0 && col >= 0 && row < size && col < size && grid[row][col].isEmpty();
    }

    public void placeMove(int row, int col, Symbol symbol) {
        grid[row][col].setSymbol(symbol);
    }

    public boolean checkWin(Symbol symbol) {
        for (WinningStrategy winningStrategy: winningStrategies) {
            if(winningStrategy.checkWinner(this, symbol)) {
                return true;
            }
        }
        return false;
    }

    public boolean isFull() {
        return movesCount == size * size;
    }

    public void reset() {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                grid[i][j].setSymbol(Symbol.EMPTY);
    }

    public void print() {
        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {
                System.out.print(grid[row][col].getSymbol() + " ");
            }
            System.out.println();
        }
        System.out.println();
    }

    public Symbol getSymbol(int row, int col) {
        return grid[row][col].getSymbol();
    }

    public int getSize() {
        return size;
    }
}
