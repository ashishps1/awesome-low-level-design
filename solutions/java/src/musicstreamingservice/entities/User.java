package musicstreamingservice.entities;

import musicstreamingservice.enums.SubscriptionTier;
import musicstreamingservice.observer.ArtistObserver;
import musicstreamingservice.strategies.playback.PlaybackStrategy;

import java.util.HashSet;
import java.util.Set;
import java.util.UUID;

public class User implements ArtistObserver {
    private final String id;
    private final String name;
    private final PlaybackStrategy playbackStrategy;
    private final Set<Artist> followedArtists = new HashSet<>();

    private User(String id, String name, PlaybackStrategy strategy) {
        this.id = id;
        this.name = name;
        this.playbackStrategy = strategy;
    }

    public void followArtist(Artist artist) {
        followedArtists.add(artist);
        artist.addObserver(this);
    }

    @Override
    public void update(Artist artist, Album newAlbum) {
        System.out.printf("[Notification for %s] Your followed artist %s just released a new album: %s!%n",
                this.name, artist.getName(), newAlbum.getTitle());
    }

    public PlaybackStrategy getPlaybackStrategy() { return playbackStrategy; }

    public String getId() { return id; }
    public String getName() { return name; }

    // Builder Pattern
    public static class Builder {
        private final String id;
        private final String name;
        private PlaybackStrategy playbackStrategy;

        public Builder(String name) {
            this.id = UUID.randomUUID().toString();
            this.name = name;
        }
        public Builder withSubscription(SubscriptionTier tier, int songsPlayed) {
            this.playbackStrategy = PlaybackStrategy.getStrategy(tier, songsPlayed);
            return this;
        }
        public User build() {
            return new User(id, name, playbackStrategy);
        }
    }
}
