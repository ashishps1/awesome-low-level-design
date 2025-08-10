interface IGameState
{
    void HandleMove(Game game, Player player, int row, int col);
}