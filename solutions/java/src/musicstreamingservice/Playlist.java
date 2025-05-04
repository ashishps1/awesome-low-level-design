package musicstreamingservice;

import java.util.List;
import java.util.UUID;
import java.util.concurrent.CopyOnWriteArrayList;

public class Playlist {
    private final String id;
    private final String name;
    private final User owner;
    private final List<Song> songs;

    public Playlist(String name, User owner) {
        this.id = UUID.randomUUID().toString();
        this.name = name;
        this.owner = owner;
        this.songs = new CopyOnWriteArrayList<>();
    }

    public void addSong(Song song) {
        songs.add(song);
    }

    public void removeSong(Song song) {
        songs.remove(song);
    }

    public List<Song> getSongs() {
        return List.copyOf(songs);
    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }
}
