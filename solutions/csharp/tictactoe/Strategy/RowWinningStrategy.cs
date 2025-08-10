class RowWinningStrategy : IWinningStrategy
{
    public bool CheckWinner(Board board, Player player)
    {
        for (int row = 0; row < board.GetSize(); row++)
        {
            bool rowWin = true;
            for (int col = 0; col < board.GetSize(); col++)
            {
                if (board.GetCell(row, col).GetSymbol() != player.GetSymbol())
                {
                    rowWin = false;
                    break;
                }
            }
            if (rowWin) return true;
        }
        return false;
    }
}