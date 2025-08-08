package musicstreamingservice.observer;

import musicstreamingservice.entities.Album;
import musicstreamingservice.entities.Artist;

public interface ArtistObserver {
    void update(Artist artist, Album newAlbum);
}
