class PremiumPlaybackStrategy : PlaybackStrategy
{
    public override void Play(Song song, Player player)
    {
        player.SetCurrentSong(song);
        Console.WriteLine($"Premium User is now playing: {song}");
    }
}