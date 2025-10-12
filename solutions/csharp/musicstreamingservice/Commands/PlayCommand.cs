class PlayCommand : ICommand
{
    private readonly Player player;

    public PlayCommand(Player player)
    {
        this.player = player;
    }

    public void Execute()
    {
        player.ClickPlay();
    }
}