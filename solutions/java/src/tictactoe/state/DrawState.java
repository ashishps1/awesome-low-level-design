package tictactoe.state;

import tictactoe.Game;
import tictactoe.exceptions.InvalidMoveException;
import tictactoe.models.Player;

public class DrawState implements GameState {
    @Override
    public void handleMove(Game game, Player player, int row, int col) {
        throw new InvalidMoveException("Game is already over. It was a draw.");
    }
}
