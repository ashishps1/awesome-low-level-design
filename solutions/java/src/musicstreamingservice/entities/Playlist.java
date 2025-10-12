package musicstreamingservice.entities;

import java.util.ArrayList;
import java.util.List;

public class Playlist implements Playable {
    private final String name;
    private final List<Song> tracks = new ArrayList<>();

    public Playlist(String name) { this.name = name; }

    public void addTrack(Song song) { tracks.add(song); }

    @Override
    public List<Song> getTracks() { return List.copyOf(tracks); }
}
