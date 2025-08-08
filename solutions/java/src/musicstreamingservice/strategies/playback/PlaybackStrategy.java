package musicstreamingservice.strategies.playback;

import musicstreamingservice.enums.SubscriptionTier;
import musicstreamingservice.entities.Player;
import musicstreamingservice.entities.Song;

public interface PlaybackStrategy {
    void play(Song song, Player player);

    // Simple Factory method to get the correct strategy
    static PlaybackStrategy getStrategy(SubscriptionTier tier, int songsPlayed) {
        return tier == SubscriptionTier.PREMIUM ? new PremiumPlaybackStrategy() : new FreePlaybackStrategy(songsPlayed);
    }
}
