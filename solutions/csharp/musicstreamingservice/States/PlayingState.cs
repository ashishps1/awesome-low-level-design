class PlayingState : PlayerState
{
    public override void Play(Player player)
    {
        Console.WriteLine("Already playing.");
    }

    public override void Pause(Player player)
    {
        Console.WriteLine("Pausing playback.");
        player.ChangeState(new PausedState());
        player.SetStatus(PlayerStatus.PAUSED);
    }

    public override void Stop(Player player)
    {
        Console.WriteLine("Stopping playback.");
        player.ChangeState(new StoppedState());
        player.SetStatus(PlayerStatus.STOPPED);
    }
}