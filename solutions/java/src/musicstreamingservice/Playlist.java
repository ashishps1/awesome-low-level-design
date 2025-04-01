package musicstreamingservice;

import java.util.ArrayList;
import java.util.List;

public class Playlist {
    private final String id;
    private final String name;
    private final User owner;
    private final List<Song> songs;

    public Playlist(String id, String name, User owner) {
        this.id = id;
        this.name = name;
        this.owner = owner;
        this.songs = new ArrayList<>();
    }

    public void addSong(Song song) {
        songs.add(song);
    }

    public void removeSong(Song song) {
        songs.remove(song);
    }

    public String getName() {
        return name;
    }

    public List<Song> getSongs() {
        return songs;
    }
}
