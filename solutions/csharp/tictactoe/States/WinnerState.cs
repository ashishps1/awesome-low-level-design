class WinnerState : IGameState
{
    public void HandleMove(Game game, Player player, int row, int col)
    {
        throw new InvalidMoveException("Game is already over. " + game.GetWinner().GetName() + " has won.");
    }
}