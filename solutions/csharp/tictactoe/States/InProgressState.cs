class InProgressState : IGameState
{
    public void HandleMove(Game game, Player player, int row, int col)
    {
        if (game.GetCurrentPlayer() != player)
        {
            throw new InvalidMoveException("Not your turn!");
        }

        // Place the piece on the board
        game.GetBoard().PlaceSymbol(row, col, player.GetSymbol());

        // Check for a winner or a draw
        if (game.CheckWinner(player))
        {
            game.SetWinner(player);
            if (player.GetSymbol() == Symbol.X)
            {
                game.SetStatus(GameStatus.WINNER_X);
            }
            else
            {
                game.SetStatus(GameStatus.WINNER_O);
            }            
            game.SetState(new WinnerState());
        }
        else if (game.GetBoard().IsFull())
        {
            game.SetStatus(GameStatus.DRAW);
            game.SetState(new DrawState());
        }
        else
        {
            // If the game is still in progress, switch players
            game.SwitchPlayer();
        }
    }
}