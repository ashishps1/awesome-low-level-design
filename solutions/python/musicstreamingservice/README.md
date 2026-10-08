# Designing an Online Music Streaming Service Like Spotify

## Requirements
1. The music streaming service should allow users to browse and search for songs, albums, and artists.
2. Users should be able to create and manage playlists.
3. The system should support user authentication and authorization.
4. Users should be able to play, pause, skip, and seek within songs.
5. The system should recommend songs and playlists based on user preferences and listening history.
6. The system should handle concurrent requests and ensure smooth streaming experience for multiple users.
7. The system should be scalable and handle a large volume of songs and users.
8. The system should be extensible to support additional features such as social sharing and offline playback.

## Implemented Classes and Services

- `MusicStreamingSystem` is the singleton facade. It registers users, stores songs and artists, searches song titles, returns recommendations, and exposes one `Player` through `get_player`.
- `Song` is a track; `Album` and `Playlist` implement the `Playable` collection interface. `Artist` notifies its observers when an album is released.
- `User.Builder` creates users with a free or premium `PlaybackStrategy`; users can follow artists. It does not implement password-based login.
- `Player` loads a `Playable` for a user and exposes play, pause, and next-track controls. It uses `StoppedState`, `PlayingState`, and `PausedState`; no seek control is implemented.
- `SearchService` searches the catalog, and `RecommendationService` delegates to a `RecommendationStrategy`. The demo uses `GenreBasedRecommendationStrategy`.
- `PlayCommand`, `PauseCommand`, and `NextTrackCommand` invoke the player controls.

The requirements above describe the broader design goals. The current example has a shared player, no authentication service, and no service API for storing playlists. See `music_streaming_demo.py` for the implemented album, playlist, free/premium playback, artist notifications, search, and recommendation flows.
