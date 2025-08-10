class ColumnWinningStrategy : IWinningStrategy
{
    public bool CheckWinner(Board board, Player player)
    {
        for (int col = 0; col < board.GetSize(); col++)
        {
            bool colWin = true;
            for (int row = 0; row < board.GetSize(); row++)
            {
                if (board.GetCell(row, col).GetSymbol() != player.GetSymbol())
                {
                    colWin = false;
                    break;
                }
            }
            if (colWin) return true;
        }
        return false;
    }
}