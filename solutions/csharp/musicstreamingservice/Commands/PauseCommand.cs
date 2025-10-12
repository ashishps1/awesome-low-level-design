class PauseCommand : ICommand
{
    private readonly Player player;

    public PauseCommand(Player player)
    {
        this.player = player;
    }

    public void Execute()
    {
        player.ClickPause();
    }
}