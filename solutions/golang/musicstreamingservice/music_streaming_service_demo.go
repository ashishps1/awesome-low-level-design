package musicstreamingservice

import (
	"fmt"
)

func Run() {
	service := NewMusicStreamingService()

	// Create users
	user1 := NewUser("1", "john@example.com", "password123")
	user2 := NewUser("2", "jane@example.com", "password456")

	// Create songs
	song1 := &Song{ID: "1", Title: "Song 1", Artist: "Artist 1", Album: "Album 1", Duration: 180}
	song2 := &Song{ID: "2", Title: "Song 2", Artist: "Artist 2", Album: "Album 2", Duration: 200}
	song3 := &Song{ID: "3", Title: "Song 3", Artist: "Artist 3", Album: "Album 3", Duration: 210}

	// Create albums
	album1 := &Album{ID: "1", Title: "Album 1", Artist: "Artist 1", Songs: []*Song{song1}}
	album2 := &Album{ID: "2", Title: "Album 2", Artist: "Artist 2", Songs: []*Song{song2}}
	album3 := &Album{ID: "3", Title: "Album 3", Artist: "Artist 3", Songs: []*Song{song3}}

	// Create artists
	artist1 := &Artist{ID: "1", Name: "Artist 1", Albums: []*Album{album1}}
	artist2 := &Artist{ID: "2", Name: "Artist 2", Albums: []*Album{album2}}
	artist3 := &Artist{ID: "3", Name: "Artist 3", Albums: []*Album{album3}}

	// Add artists to library
	service.MusicLibrary.AddArtist(artist1)
	service.MusicLibrary.AddArtist(artist2)
	service.MusicLibrary.AddArtist(artist3)

	// Register users
	service.UserManager.RegisterUser(user1)
	service.UserManager.RegisterUser(user2)

	// Login user
	loggedInUser := service.UserManager.LoginUser("john@example.com", "password123")
	if loggedInUser != nil {
		fmt.Printf("User logged in: %s\n", loggedInUser.Username)
	} else {
		fmt.Println("Invalid username or password.")
	}

	// Search songs
	searchResults := service.MusicLibrary.SearchSongs("Song")
	fmt.Println("\nSearch Results:")
	for _, song := range searchResults {
		fmt.Printf("Song: %s - %s\n", song.Title, song.Artist)
	}

	// Create playlist
	playlist := NewPlaylist("1", "My Playlist", loggedInUser)
	playlist.AddSong(song1)
	playlist.AddSong(song2)
	loggedInUser.AddPlaylist(playlist)

	// Get recommendations
	recommendations := service.MusicRecommender.RecommendSongs(loggedInUser)
	fmt.Println("\nRecommended Songs:")
	for _, song := range recommendations {
		fmt.Printf("Song: %s - %s\n", song.Title, song.Artist)
	}

	// Create and use music player
	player := NewMusicPlayer()
	player.PlaySong(song1)
	player.PauseSong()
	player.SeekTo(60)

	// Display user playlists
	fmt.Println("\nUser Playlists:")
	for _, p := range loggedInUser.Playlists {
		fmt.Printf("Playlist: %s\n", p.Name)
		fmt.Println("Songs:")
		for _, s := range p.Songs {
			fmt.Printf("- %s\n", s.Title)
		}
	}
}
