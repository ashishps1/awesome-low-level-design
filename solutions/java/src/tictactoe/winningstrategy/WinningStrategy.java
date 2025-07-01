package tictactoe.winningstrategy;

import tictactoe.Board;
import tictactoe.Symbol;

public interface WinningStrategy {
    boolean checkWinner(Board board, Symbol symbol);
}
