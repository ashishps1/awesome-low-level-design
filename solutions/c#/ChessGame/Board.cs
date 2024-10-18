using System;

namespace ChessGame
{
    public class Board
    {
        private readonly Piece[,] board;

        public Board()
        {
            board = new Piece[8, 8];
            InitializeBoard();
        }

        private void InitializeBoard()
        {
            // Initialize white pieces
            board[0, 0] = new Rook(Color.White, 0, 0);
            board[0, 1] = new Knight(Color.White, 0, 1);
            board[0, 2] = new Bishop(Color.White, 0, 2);
            board[0, 3] = new Queen(Color.White, 0, 3);
            board[0, 4] = new King(Color.White, 0, 4);
            board[0, 5] = new Bishop(Color.White, 0, 5);
            board[0, 6] = new Knight(Color.White, 0, 6);
            board[0, 7] = new Rook(Color.White, 0, 7);
            for (int i = 0; i < 8; i++)
            {
                board[1, i] = new Pawn(Color.White, 1, i);
            }

            // Initialize black pieces
            board[7, 0] = new Rook(Color.Black, 7, 0);
            board[7, 1] = new Knight(Color.Black, 7, 1);
            board[7, 2] = new Bishop(Color.Black, 7, 2);
            board[7, 3] = new Queen(Color.Black, 7, 3);
            board[7, 4] = new King(Color.Black, 7, 4);
            board[7, 5] = new Bishop(Color.Black, 7, 5);
            board[7, 6] = new Knight(Color.Black, 7, 6);
            board[7, 7] = new Rook(Color.Black, 7, 7);
            for (int i = 0; i < 8; i++)
            {
                board[6, i] = new Pawn(Color.Black, 6, i);
            }
        }

        public Piece GetPiece(int row, int col)
        {
            return board[row, col];
        }

        public void SetPiece(int row, int col, Piece piece)
        {
            board[row, col] = piece;
        }

        public bool IsValidMove(Piece piece, int destRow, int destCol)
        {
            if (piece == null || destRow < 0 || destRow > 7 || destCol < 0 || destCol > 7)
            {
                return false;
            }
            Piece destPiece = board[destRow, destCol];
            return (destPiece == null || destPiece.Color != piece.Color) && piece.CanMove(this, destRow, destCol);
        }

        public bool IsCheckmate(Color color)
        {
            // TODO: Implement checkmate logic
            return false;
        }

        public bool IsStalemate(Color color)
        {
            // TODO: Implement stalemate logic
            return false;
        }
    }
}