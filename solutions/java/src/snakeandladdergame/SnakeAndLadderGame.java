package snakeandladdergame;

import java.util.ArrayList;
import java.util.List;

public class SnakeAndLadderGame {
    private final Board board;
    private final List<Player> players;
    private final Dice dice;
    private int currentPlayerIndex;

    public SnakeAndLadderGame(List<String> playerNames) {
        board = new Board();
        dice = new Dice();
        players = new ArrayList<>();
        for (String playerName : playerNames) {
            players.add(new Player(playerName));
        }
        currentPlayerIndex = 0;
    }

    public void play() {
        while (!isGameOver()) {
            Player currentPlayer = players.get(currentPlayerIndex);
            int diceRoll = dice.roll();
            int newPosition = currentPlayer.getPosition() + diceRoll;

            if (newPosition <= board.getBoardSize()) {
                currentPlayer.setPosition(board.getNewPositionAfterSnakeOrLadder(newPosition));
                System.out.println(currentPlayer.getName() + " rolled a " + diceRoll +
                        " and moved to position " + currentPlayer.getPosition());
            }

            if (currentPlayer.getPosition() == board.getBoardSize()) {
                System.out.println(currentPlayer.getName() + " wins!");
                break;
            }

            currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
        }
    }

    private boolean isGameOver() {
        for (Player player : players) {
            if (player.getPosition() == board.getBoardSize()) {
                return true;
            }
        }
        return false;
    }
}
