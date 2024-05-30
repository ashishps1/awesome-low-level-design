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

    public void makeMove(Board board, Move move) {
        Piece piece = move.getPiece();
        int destRow = move.getDestRow();
        int destCol = move.getDestCol();

        if (board.isValidMove(piece, destRow, destCol)) {
            int sourceRow = piece.getRow();
            int sourceCol = piece.getCol();
            board.setPiece(sourceRow, sourceCol, null);
            board.setPiece(destRow, destCol, piece);
            piece.setRow(destRow);
            piece.setCol(destCol);
        } else {
            throw new InvalidMoveException("Invalid move!");
        }
    }
}
