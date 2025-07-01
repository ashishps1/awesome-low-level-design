package snakeandladdergame;

import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

public class Game {
    private final Board board;
    private final Queue<Player> players;
    private final Dice dice;

    private Game(Builder builder) {
        this.board = builder.board;
        this.players = new LinkedList<>(builder.players);
        this.dice = builder.dice;
    }

    public void play() {
        while (!isGameOver()) {
            Player currentPlayer = players.poll();
            int diceRoll = dice.roll();
            int newPosition = currentPlayer.getPosition() + diceRoll;

            if (newPosition <= board.getBoardSize()) {
                currentPlayer.setPosition(board.getNextPosition(newPosition));
                System.out.println(currentPlayer.getName() + " rolled a " + diceRoll +
                        " and moved to position " + currentPlayer.getPosition());
            }

            if (currentPlayer.getPosition() == board.getBoardSize()) {
                System.out.println(currentPlayer.getName() + " wins!");
                break;
            }

            players.offer(currentPlayer);
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

    // 🧱 Inner Builder class
    public static class Builder {
        private Board board;
        private Queue<Player> players;
        private Dice dice;

        public Builder setBoard(Board board) {
            this.board = board;
            return this;
        }

        public Builder setPlayers(List<String> playerNames) {
            this.players = new LinkedList<>();
            for (String playerName : playerNames) {
                players.add(new Player(playerName));
            }
            return this;
        }

        public Builder setDice(Dice dice) {
            this.dice = dice;
            return this;
        }

        public Game build() {
            if (board == null || players == null || dice == null) {
                throw new IllegalStateException("Board, Players, and Dice must be set.");
            }
            return new Game(this);
        }
    }
}
