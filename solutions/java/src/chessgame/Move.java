package chessgame;

import chessgame.pieces.Piece;

public class Move {
    private final Piece piece;
    private final int destRow;
    private final int destCol;

    public Move(Piece piece, int destRow, int destCol) {
        this.piece = piece;
        this.destRow = destRow;
        this.destCol = destCol;
    }

    public Piece getPiece() {
        return piece;
    }

    public int getDestRow() {
        return destRow;
    }

    public int getDestCol() {
        return destCol;
    }
}
