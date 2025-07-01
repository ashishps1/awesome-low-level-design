package snakeandladdergame;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Board {
    private final int boardSize;
    private final Map<Integer, Integer> snakes;
    private final Map<Integer, Integer> ladders;

    public Board(int boardSize, List<Snake> snakeList, List<Ladder> ladderList) {
        this.boardSize = boardSize;
        snakes = new HashMap<>();
        ladders = new HashMap<>();

        for (Snake s : snakeList) {
            snakes.put(s.getHead(), s.getTail());
        }
        for (Ladder l : ladderList) {
            ladders.put(l.getStart(), l.getEnd());
        }
    }

    public int getBoardSize() {
        return boardSize;
    }

    public int getNextPosition(int currentPosition) {
        int newPosition = currentPosition;

        if (snakes.containsKey(currentPosition)) {
            System.out.println("Oops! Bitten by snake 🐍");
            newPosition =  snakes.get(currentPosition);
        } else if (ladders.containsKey(currentPosition)) {
            System.out.println("Yay! Climbed a ladder 🪜");
            newPosition = ladders.get(currentPosition);
        }

        return newPosition;
    }
}
