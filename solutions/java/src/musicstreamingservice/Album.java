package musicstreamingservice;

import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

public class Album {
    private final String id;
    private final String title;
    private final Artist artist;
    private final List<Song> songs;

    public Album(String title, Artist artist) {
        this.id = UUID.randomUUID().toString();
        this.title = title;
        this.artist = artist;
        this.songs = new ArrayList<>();
    }

    public void addSong(Song song) {
        songs.add(song);
    }

    public void addSongs(List<Song> songs) {
        this.songs.addAll(songs);
    }

    public List<Song> getSongs() {
        return songs;
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
}
