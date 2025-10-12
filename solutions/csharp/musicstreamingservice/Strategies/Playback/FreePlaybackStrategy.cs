class FreePlaybackStrategy : PlaybackStrategy
{
    private int songsPlayed;
    private const int SONGS_BEFORE_AD = 3;

    public FreePlaybackStrategy(int initialSongsPlayed)
    {
        this.songsPlayed = initialSongsPlayed;
    }

    public override void Play(Song song, Player player)
    {
        if (songsPlayed > 0 && songsPlayed % SONGS_BEFORE_AD == 0)
        {
            Console.WriteLine("\n>>> Playing Advertisement: 'Buy Spotify Premium for ad-free music!' <<<\n");
        }
        player.SetCurrentSong(song);
        Console.WriteLine($"Free User is now playing: {song}");
        songsPlayed++;
    }
}