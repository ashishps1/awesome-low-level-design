package snakeandladdergame;

import java.util.ArrayList;
import java.util.List;

public class Board {
    private static final int BOARD_SIZE = 100;
    private final List<Snake> snakes;
    private final List<Ladder> ladders;

    public Board() {
        snakes = new ArrayList<>();
        ladders = new ArrayList<>();
        initializeSnakesAndLadders();
    }

    private void initializeSnakesAndLadders() {
        // Initialize snakes
        snakes.add(new Snake(16, 6));
        snakes.add(new Snake(48, 26));
        snakes.add(new Snake(64, 60));
        snakes.add(new Snake(93, 73));

        // Initialize ladders
        ladders.add(new Ladder(1, 38));
        ladders.add(new Ladder(4, 14));
        ladders.add(new Ladder(9, 31));
        ladders.add(new Ladder(21, 42));
        ladders.add(new Ladder(28, 84));
        ladders.add(new Ladder(51, 67));
        ladders.add(new Ladder(80, 99));
    }

    public int getBoardSize() {
        return BOARD_SIZE;
    }

    public int getNewPositionAfterSnakeOrLadder(int position) {
        for (Snake snake : snakes) {
            if (snake.getStart() == position) {
                return snake.getEnd();
            }
        }

        for (Ladder ladder : ladders) {
            if (ladder.getStart() == position) {
                return ladder.getEnd();
            }
        }

        return position;
    }
}
