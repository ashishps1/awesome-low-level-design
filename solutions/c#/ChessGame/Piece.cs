namespace ChessGame
{
    public abstract class Piece
    {
        public Color Color { get; }
        public int Row { get; set; }
        public int Col { get; set; }

        public Piece(Color color, int row, int col)
        {
            Color = color;
            Row = row;
            Col = col;
        }

        public abstract bool CanMove(Board board, int destRow, int destCol);
    }
}