package musicstreamingservice;

import java.util.List;

public class Artist {
    private final String id;
    private final String name;
    private final List<Album> albums;

    public Artist(String id, String name, List<Album> albums) {
        this.id = id;
        this.name = name;
        this.albums = albums;
    }

    public String getId() {
        return id;
    }

    public List<Album> getAlbums() {
        return albums;
    }
}
