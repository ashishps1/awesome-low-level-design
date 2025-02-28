namespace ChessGame
{
    public class King : Piece
    {
        public King(Color color, int row, int col) : base(color, row, col) { }

        public override bool CanMove(Board board, int destRow, int destCol)
        {
            int rowDiff = System.Math.Abs(destRow - Row);
            int colDiff = System.Math.Abs(destCol - Col);
            return rowDiff <= 1 && colDiff <= 1;
        }
    }    
}