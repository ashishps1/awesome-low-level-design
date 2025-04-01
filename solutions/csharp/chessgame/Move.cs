namespace ChessGame
{
    public class Move
    {
        public Piece Piece { get; }
        public int DestRow { get; }
        public int DestCol { get; }

        public Move(Piece piece, int destRow, int destCol)
        {
            Piece = piece;
            DestRow = destRow;
            DestCol = destCol;
        }
    }
}