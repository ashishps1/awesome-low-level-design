package tictactoe.winningstrategy;

import tictactoe.Board;
import tictactoe.Symbol;

public class ColumnWinningStrategy implements WinningStrategy {
    @Override
    public boolean checkWinner(Board board, Symbol symbol) {
        for (int i = 0; i < board.getSize(); i++) {
            boolean allMatch = true;
            for (int j = 0; j < board.getSize(); j++) {
                if (board.getSymbol(j, i) != symbol) {
                    allMatch = false;
                    break;
                }
            }
            if (allMatch) return true;
        }
        return false;
    }
}
