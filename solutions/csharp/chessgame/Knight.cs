namespace ChessGame
{
    public class Knight : Piece
    {
        public Knight(Color color, int row, int col) : base(color, row, col) { }

        public override bool CanMove(Board board, int destRow, int destCol)
        {
            int rowDiff = System.Math.Abs(destRow - Row);
            int colDiff = System.Math.Abs(destCol - Col);
            return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
        }
    }
}