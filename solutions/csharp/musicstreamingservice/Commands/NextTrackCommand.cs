class NextTrackCommand : ICommand
{
    private readonly Player player;

    public NextTrackCommand(Player player)
    {
        this.player = player;
    }

    public void Execute()
    {
        player.ClickNext();
    }
}