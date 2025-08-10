abstract class PlaybackStrategy
{
    public abstract void Play(Song song, Player player);

    public static PlaybackStrategy GetStrategy(SubscriptionTier tier, int songsPlayed)
    {
        if (tier == SubscriptionTier.PREMIUM)
        {
            return new PremiumPlaybackStrategy();
        }
        else
        {
            return new FreePlaybackStrategy(songsPlayed);
        }
    }
}