class PausedState : PlayerState
{
    public override void Play(Player player)
    {
        Console.WriteLine("Resuming playback.");
        player.ChangeState(new PlayingState());
        player.SetStatus(PlayerStatus.PLAYING);
    }

    public override void Pause(Player player)
    {
        Console.WriteLine("Already paused.");
    }

    public override void Stop(Player player)
    {
        Console.WriteLine("Stopping playback from paused state.");
        player.ChangeState(new StoppedState());
        player.SetStatus(PlayerStatus.STOPPED);
    }
}