package chessgame;

import chessgame.pieces.Piece;

public class Player {
    private final Color color;

    public Player(Color color) {
        this.color = color;
    }

    public Color getColor() {
        return color;
    }
}
