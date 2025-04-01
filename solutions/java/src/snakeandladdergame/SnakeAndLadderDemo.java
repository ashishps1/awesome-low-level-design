package snakeandladdergame;

import java.util.Arrays;
import java.util.List;

public class SnakeAndLadderDemo {
    public static void run() {
        GameManager gameManager = GameManager.getInstance();

        // Start game 1
        List<String> players1 = Arrays.asList("Player 1", "Player 2", "Player 3");
        gameManager.startNewGame(players1);

        // Start game 2
        List<String> players2 = Arrays.asList("Player 4", "Player 5");
        gameManager.startNewGame(players2);
    }
}
