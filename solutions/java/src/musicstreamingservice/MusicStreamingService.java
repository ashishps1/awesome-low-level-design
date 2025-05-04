package musicstreamingservice;

import java.time.Duration;
import java.util.ArrayList;
import java.util.List;

public class MusicStreamingService {
    private final MusicLibrary musicLibrary;
    private final UserManager userManager;
    private final MusicRecommender musicRecommender;

    public MusicStreamingService() {
        musicLibrary = MusicLibrary.getInstance();
        userManager = UserManager.getInstance();
        musicRecommender = MusicRecommender.getInstance();
    }

    public User registerUser(String username, String password) {
        User user = new User(username, password);
        userManager.registerUser(user);
        return user;
    }

    public Song addNewSong(String title, String artistId, String albumId, Duration duration) {
        Artist artist = musicLibrary.getArtist(artistId);
        Album album = musicLibrary.getAlbum(albumId);
        Song song = new Song(title, artist, album, duration);
        musicLibrary.addSong(song);
        return song;
    }

    public Artist addNewArtist(String name) {
        Artist artist = new Artist(name);
        musicLibrary.addArtist(artist);
        return artist;
    }

    public Album addNewAlbum(String name, String artistId) {
        Artist artist = musicLibrary.getArtist(artistId);
        Album album = new Album(name, artist);
        musicLibrary.addAlbum(album);
        return album;
    }

    public void addAlbumToArtist(String artistId, String albumId) {
        Artist artist = musicLibrary.getArtist(artistId);
        Album album = musicLibrary.getAlbum(albumId);
        artist.addAlbum(album);
    }

    public void addSongsToAlbum(String albumId, List<String> songIds) {
        List<Song> songs = new ArrayList<>();

        for(String songId: songIds) {
            songs.add(musicLibrary.getSong(songId));
        }

        Album album = musicLibrary.getAlbum(albumId);
        album.addSongs(songs);
    }

    public void playSong(String userId, String songId) {
        User user = userManager.getUser(userId);
        Song song = musicLibrary.getSong(songId);
        if (user == null || song == null) throw new IllegalArgumentException("Invalid user or song");
        user.play(song);
    }

    public void pauseSong(String userId) {
        User user = userManager.getUser(userId);
        if (user == null) throw new IllegalArgumentException("Invalid user");
        user.pause();
    }

    public Playlist createPlaylist(String userId, String name) {
        User user = userManager.getUser(userId);
        if (user == null) throw new IllegalArgumentException("Invalid user");
        return user.createPlaylist(name);
    }

    public void addSongToPlaylist(String userId, String playlistId, String songId) {
        Song song = musicLibrary.getSong(songId);
        Playlist playlist = userManager.getUserPlaylist(userId, playlistId);
        playlist.addSong(song);
    }

    public List<Song> searchSongs(String query) {
        List<Song> matchingSongs = new ArrayList<>();
        for (Song song : musicLibrary.getSongs()) {
            if (song.getTitle().contains(query)
                    || song.getArtist().getName().contains(query)
                    || song.getAlbum().getTitle().contains(query)) {
                matchingSongs.add(song);
            }
        }
        return matchingSongs;
    }
}
