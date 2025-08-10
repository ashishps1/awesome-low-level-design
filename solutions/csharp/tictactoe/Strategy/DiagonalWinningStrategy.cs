class DiagonalWinningStrategy : IWinningStrategy
{
    public bool CheckWinner(Board board, Player player)
    {
        // Main diagonal
        bool mainDiagWin = true;
        for (int i = 0; i < board.GetSize(); i++)
        {
            if (board.GetCell(i, i).GetSymbol() != player.GetSymbol())
            {
                mainDiagWin = false;
                break;
            }
        }
        if (mainDiagWin) return true;

        // Anti-diagonal
        bool antiDiagWin = true;
        for (int i = 0; i < board.GetSize(); i++)
        {
            if (board.GetCell(i, board.GetSize() - 1 - i).GetSymbol() != player.GetSymbol())
            {
                antiDiagWin = false;
                break;
            }
        }
        return antiDiagWin;
    }
}