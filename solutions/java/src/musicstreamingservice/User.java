package musicstreamingservice;

import java.util.*;

public class User {
    private final String id;
    private final String username;
    private final String password;
    private final Map<String, Playlist> playlists;
    private final PlaybackSession playback;

    public User(String username, String password) {
        this.id = UUID.randomUUID().toString();
        this.username = username;
        this.password = password;
        this.playback = new PlaybackSession();
        this.playlists = new HashMap<>();
    }

    public Playlist createPlaylist(String name) {
        Playlist playlist = new Playlist(name, this);
        playlists.put(playlist.getId(), playlist);
        return playlist;
    }

    public void removePlaylist(String name) {
        Playlist playlist = playlists.get(name);
        playlists.remove(name);
    }

    public void play(Song song) {
        playback.play(song);
    }

    public void pause() {
        playback.pause();
    }

    public String getId() {
        return id;
    }

    public String getUsername() {
        return username;
    }

    public String getPassword() {
        return password;
    }

    public Playlist getPlaylist(String playlistId) {
        return playlists.get(playlistId);
    }

    public List<Playlist> getPlaylists() {
        return playlists.values().stream().toList();
    }
}
