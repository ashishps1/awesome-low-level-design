namespace ChessGame
{
    public class Pawn : Piece
    {
        public Pawn(Color color, int row, int col) : base(color, row, col) { }

        public override bool CanMove(Board board, int destRow, int destCol)
        {
            int rowDiff = destRow - Row;
            int colDiff = System.Math.Abs(destCol - Col);

            if (Color == Color.White)
            {
                return (rowDiff == 1 && colDiff == 0) ||
                       (Row == 1 && rowDiff == 2 && colDiff == 0) ||
                       (rowDiff == 1 && colDiff == 1 && board.GetPiece(destRow, destCol) != null);
            }
            else
            {
                return (rowDiff == -1 && colDiff == 0) ||
                       (Row == 6 && rowDiff == -2 && colDiff == 0) ||
                       (rowDiff == -1 && colDiff == 1 && board.GetPiece(destRow, destCol) != null);
            }
        }
    }    
}