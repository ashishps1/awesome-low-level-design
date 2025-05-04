package musicstreamingservice;

import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

public class Artist {
    private final String id;
    private final String name;
    private final List<Album> albums;

    public Artist(String name) {
        this.id = UUID.randomUUID().toString();
        this.name = name;
        this.albums = new ArrayList<>();
    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public void addAlbum(Album album) {
        albums.add(album);
    }

    public void addAlbums(List<Album> albums) {
        this.albums.addAll(albums);
    }

    public List<Album> getAlbums() {
        return albums;
    }
}
