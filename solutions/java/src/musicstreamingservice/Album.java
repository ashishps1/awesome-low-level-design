package musicstreamingservice;

import java.util.List;

public class Album {
    private final String id;
    private final String title;
    private final String artist;
    private final List<Song> songs;

    public Album(String id, String title, String artist, List<Song> songs) {
        this.id = id;
        this.title = title;
        this.artist = artist;
        this.songs = songs;
    }

    public String getId() {
        return id;
    }

    public String getTitle() {
        return title;
    }

    public String getArtist() {
        return artist;
    }

    public List<Song> getSongs() {
        return songs;
    }
}
