namespace ChessGame
{
    public class Player
    {
        public Color Color { get; }

        public Player(Color color)
        {
            Color = color;
        }

        public void MakeMove(Board board, Move move)
        {
            Piece piece = move.Piece;
            int destRow = move.DestRow;
            int destCol = move.DestCol;

            if (board.IsValidMove(piece, destRow, destCol))
            {
                int sourceRow = piece.Row;
                int sourceCol = piece.Col;
                board.SetPiece(sourceRow, sourceCol, null);
                board.SetPiece(destRow, destCol, piece);
                piece.Row = destRow;
                piece.Col = destCol;
            }
            else
            {
                throw new InvalidMoveException("Invalid move!");
            }
        }
    }
}