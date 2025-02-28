namespace ChessGame
{
    public class Rook : Piece
    {
        public Rook(Color color, int row, int col) : base(color, row, col) { }

        public override bool CanMove(Board board, int destRow, int destCol)
        {
            return Row == destRow || Col == destCol;
        }
    }    
}