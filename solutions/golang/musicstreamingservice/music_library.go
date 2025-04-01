package musicstreamingservice

import (
	"strings"
	"sync"
)

type MusicLibrary struct {
	songs   map[string]*Song
	albums  map[string]*Album
	artists map[string]*Artist
	mu      sync.RWMutex
}

var (
	libraryInstance *MusicLibrary
	libraryOnce     sync.Once
)

func GetMusicLibrary() *MusicLibrary {
	libraryOnce.Do(func() {
		libraryInstance = &MusicLibrary{
			songs:   make(map[string]*Song),
			albums:  make(map[string]*Album),
			artists: make(map[string]*Artist),
		}
	})
	return libraryInstance
}

func (ml *MusicLibrary) AddSong(song *Song) {
	ml.mu.Lock()
	defer ml.mu.Unlock()
	ml.songs[song.ID] = song
}

func (ml *MusicLibrary) AddAlbum(album *Album) {
	ml.mu.Lock()
	defer ml.mu.Unlock()
	ml.albums[album.ID] = album
	for _, song := range album.Songs {
		ml.songs[song.ID] = song
	}
}

func (ml *MusicLibrary) AddArtist(artist *Artist) {
	ml.mu.Lock()
	defer ml.mu.Unlock()
	ml.artists[artist.ID] = artist
	for _, album := range artist.Albums {
		ml.albums[album.ID] = album
		for _, song := range album.Songs {
			ml.songs[song.ID] = song
		}
	}
}

func (ml *MusicLibrary) SearchSongs(query string) []*Song {
	ml.mu.RLock()
	defer ml.mu.RUnlock()

	query = strings.ToLower(query)
	var results []*Song

	for _, song := range ml.songs {
		if strings.Contains(strings.ToLower(song.Title), query) ||
			strings.Contains(strings.ToLower(song.Artist), query) ||
			strings.Contains(strings.ToLower(song.Album), query) {
			results = append(results, song)
		}
	}
	return results
}
