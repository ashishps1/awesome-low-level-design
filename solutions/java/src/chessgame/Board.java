package chessgame;

import chessgame.pieces.*;

public class Board {
    private final Piece[][] board;

    public Board() {
        board = new Piece[8][8];
        initializeBoard();
    }

    private void initializeBoard() {
        // Initialize white pieces
        board[0][0] = new Rook(Color.WHITE, 0, 0);
        board[0][1] = new Knight(Color.WHITE, 0, 1);
        board[0][2] = new Bishop(Color.WHITE, 0, 2);
        board[0][3] = new Queen(Color.WHITE, 0, 3);
        board[0][4] = new King(Color.WHITE, 0, 4);
        board[0][5] = new Bishop(Color.WHITE, 0, 5);
        board[0][6] = new Knight(Color.WHITE, 0, 6);
        board[0][7] = new Rook(Color.WHITE, 0, 7);
        for (int i = 0; i < 8; i++) {
            board[1][i] = new Pawn(Color.WHITE, 1, i);
        }

        // Initialize black pieces
        board[7][0] = new Rook(Color.BLACK, 7, 0);
        board[7][1] = new Knight(Color.BLACK, 7, 1);
        board[7][2] = new Bishop(Color.BLACK, 7, 2);
        board[7][3] = new Queen(Color.BLACK, 7, 3);
        board[7][4] = new King(Color.BLACK, 7, 4);
        board[7][5] = new Bishop(Color.BLACK, 7, 5);
        board[7][6] = new Knight(Color.BLACK, 7, 6);
        board[7][7] = new Rook(Color.BLACK, 7, 7);
        for (int i = 0; i < 8; i++) {
            board[6][i] = new Pawn(Color.BLACK, 6, i);
        }
    }

    public Piece getPiece(int row, int col) {
        return board[row][col];
    }

    public void setPiece(int row, int col, Piece piece) {
        board[row][col] = piece;
    }

    public boolean isValidMove(Piece piece, int destRow, int destCol) {
        if (piece == null || destRow < 0 || destRow > 7 || destCol < 0 || destCol > 7) {
            return false;
        }
        Piece destPiece = board[destRow][destCol];
        return (destPiece == null || destPiece.getColor() != piece.getColor()) &&
                piece.canMove(this, destRow, destCol);
    }

    public boolean isCheckmate(Color color) {
        // TODO: Implement checkmate logic
        return false;
    }

    public boolean isStalemate(Color color) {
        // TODO: Implement stalemate logic
        return false;
    }
}
