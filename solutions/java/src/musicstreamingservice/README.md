# Music Streaming Service (LLD)

## Problem Statement

Design and implement an online music streaming service (like Spotify) that allows users to browse, search, and play songs, manage playlists, follow artists, and receive recommendations.

---

## Requirements

- **User Management:** Users can register, log in, and manage their profiles.
- **Browse & Search:** Users can browse and search for songs, albums, and artists.
- **Playlists:** Users can create, update, and manage playlists.
- **Playback Controls:** Users can play, pause, skip, and seek within songs.
- **Recommendations:** The system recommends songs and playlists based on user preferences and listening history.
- **Follow Artists:** Users can follow artists to get updates and recommendations.
- **Concurrency:** The system handles concurrent requests and smooth streaming for multiple users.
- **Scalability:** The system is scalable to handle a large volume of songs and users.
- **Extensibility:** Easy to add features like social sharing, offline playback, or collaborative playlists.

---

## Core Entities

- **Song:** Represents a song with properties like ID, title, artist, album, and duration.
- **Album:** Represents an album containing multiple songs and associated with an artist.
- **Artist:** Represents a music artist, with a list of albums and songs.
- **User:** Represents a user with ID, username, password, playlists, and listening history.
- **Playlist:** Represents a user-created playlist containing a list of songs.
- **MusicLibrary:** Central repository for storing and managing songs, albums, and artists (Singleton).
- **UserManager:** Handles user registration, login, and user-related operations (Singleton).
- **MusicPlayer:** Handles music playback (play, pause, skip, seek).
- **MusicRecommender:** Generates song and playlist recommendations based on user preferences and history (Singleton).
- **MusicStreamingService:** Main entry point, initializes components, handles user requests, and manages overall functionality.

---

## Class Design

### 1. Song
- **Fields:** int id, String title, Artist artist, Album album, int duration
- **Methods:** getId(), getTitle(), getArtist(), getAlbum(), getDuration()

### 2. Album
- **Fields:** int id, String title, Artist artist, List<Song> songs
- **Methods:** getId(), getTitle(), getArtist(), getSongs()

### 3. Artist
- **Fields:** int id, String name, List<Album> albums, List<Song> songs
- **Methods:** getId(), getName(), getAlbums(), getSongs()

### 4. User
- **Fields:** int id, String username, String password, List<Playlist> playlists, List<Song> listeningHistory, List<Artist> followedArtists
- **Methods:** getId(), getUsername(), getPlaylists(), followArtist(Artist), etc.

### 5. Playlist
- **Fields:** int id, String name, List<Song> songs
- **Methods:** addSong(Song), removeSong(Song), getSongs()

### 6. MusicLibrary (Singleton)
- **Fields:** Map<Integer, Song> songs, Map<Integer, Album> albums, Map<Integer, Artist> artists
- **Methods:** addSong(Song), addAlbum(Album), addArtist(Artist), searchSongs(String), searchAlbums(String), searchArtists(String)

### 7. UserManager (Singleton)
- **Fields:** Map<Integer, User> users
- **Methods:** registerUser(...), login(...), getUser(int id)

### 8. MusicPlayer
- **Fields:** Song currentSong, int currentPosition, boolean isPlaying
- **Methods:** play(Song), pause(), skip(), seek(int position)

### 9. MusicRecommender (Singleton)
- **Methods:** recommendSongs(User), recommendPlaylists(User)

### 10. MusicStreamingService
- **Fields:** MusicLibrary library, UserManager userManager, MusicPlayer player, MusicRecommender recommender
- **Methods:** initialize(), handleUserRequest(...), etc.

---

## Design Patterns Used

- **Singleton Pattern:** For `MusicLibrary`, `UserManager`, and `MusicRecommender` to ensure a single instance.
---

## Example Usage

```java
MusicStreamingService service = new MusicStreamingService();
service.initialize();

User alice = service.getUserManager().registerUser("alice", "password");
Artist artist = new Artist(1, "The Beatles");
Album album = new Album(1, "Abbey Road", artist);
Song song = new Song(1, "Come Together", artist, album, 259);

service.getLibrary().addArtist(artist);
service.getLibrary().addAlbum(album);
service.getLibrary().addSong(song);

alice.getPlaylists().add(new Playlist(1, "Favorites"));
alice.getPlaylists().get(0).addSong(song);

service.getPlayer().play(song);
```

---

## Demo

See `MusicStreamingServiceDemo.java` for a sample usage and simulation of the music streaming service.

---

## Extending the Framework

- **Add social features:** Allow users to share playlists or follow each other.
- **Add offline playback:** Support downloading songs for offline listening.
- **Add collaborative playlists:** Allow multiple users to edit a playlist.

---