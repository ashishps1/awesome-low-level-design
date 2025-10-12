class StoppedState : PlayerState
{
    public override void Play(Player player)
    {
        if (player.HasQueue())
        {
            Console.WriteLine("Starting playback.");
            player.ChangeState(new PlayingState());
            player.SetStatus(PlayerStatus.PLAYING);
            player.PlayCurrentSongInQueue();
        }
        else
        {
            Console.WriteLine("Queue is empty. Load songs to play.");
        }
    }

    public override void Pause(Player player)
    {
        Console.WriteLine("Cannot pause. Player is stopped.");
    }

    public override void Stop(Player player)
    {
        Console.WriteLine("Already stopped.");
    }
}