package musicstreamingservice

import "sync"

type User struct {
	ID        string
	Username  string
	Password  string
	Playlists []*Playlist
	mu        sync.RWMutex
}

func NewUser(id, username, password string) *User {
	return &User{
		ID:        id,
		Username:  username,
		Password:  password,
		Playlists: make([]*Playlist, 0),
	}
}

func (u *User) AddPlaylist(playlist *Playlist) {
	u.mu.Lock()
	defer u.mu.Unlock()
	u.Playlists = append(u.Playlists, playlist)
}

func (u *User) RemovePlaylist(playlist *Playlist) {
	u.mu.Lock()
	defer u.mu.Unlock()
	for i, p := range u.Playlists {
		if p.ID == playlist.ID {
			u.Playlists = append(u.Playlists[:i], u.Playlists[i+1:]...)
			return
		}
	}
}
