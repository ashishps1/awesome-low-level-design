class DrawState : IGameState
{
    public void HandleMove(Game game, Player player, int row, int col)
    {
        throw new InvalidMoveException("Game is already over. It was a draw.");
    }
}