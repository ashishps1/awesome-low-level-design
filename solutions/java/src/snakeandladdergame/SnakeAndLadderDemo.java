package snakeandladdergame;

import java.util.Arrays;
import java.util.List;

public class SnakeAndLadderDemo {
    public static void run() {
        // Start game 1
        List<Snake> snakes = List.of(
                new Snake(17, 7), new Snake(54, 34),
                new Snake(62, 19), new Snake(98, 79)
        );

        List<Ladder> ladders = List.of(
                new Ladder(3, 38), new Ladder(24, 33),
                new Ladder(42, 93), new Ladder(72, 84)
        );

        Board board = new Board(100, snakes, ladders);

        List<String> players = Arrays.asList("Player 1", "Player 2", "Player 3");

        SnakeAndLadderGame game = new SnakeAndLadderGame(board, players, new Dice(1, 6));

        game.play();
    }
}
