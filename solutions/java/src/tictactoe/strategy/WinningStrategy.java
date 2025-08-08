package tictactoe.strategy;

import tictactoe.models.Board;
import tictactoe.models.Player;

public interface WinningStrategy {
    boolean checkWinner(Board board, Player player);
}
