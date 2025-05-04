package musicstreamingservice;

import java.time.Duration;
import java.util.UUID;

public class Song {
    private final String id;
    private final String title;
    private final Artist artist;
    private final Album album;
    private final Duration duration;

    public Song(String title, Artist artist, Album album, Duration duration) {
        this.id = UUID.randomUUID().toString();
        this.title = title;
        this.artist = artist;
        this.album = album;
        this.duration = duration;
    }

    public String getId() {
        return id;
    }

    public String getTitle() {
        return title;
    }

    public Artist getArtist() {
        return artist;
    }

    public String getArtistName() {
        return artist.getName();
    }

    public Album getAlbum() {
        return album;
    }
}
