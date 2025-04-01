package musicstreamingservice

type Playlist struct {
	ID    string
	Name  string
	Owner *User
	Songs []*Song
}

func NewPlaylist(id, name string, owner *User) *Playlist {
	return &Playlist{
		ID:    id,
		Name:  name,
		Owner: owner,
		Songs: make([]*Song, 0),
	}
}

func (p *Playlist) AddSong(song *Song) {
	p.Songs = append(p.Songs, song)
}

func (p *Playlist) RemoveSong(song *Song) {
	for i, s := range p.Songs {
		if s.ID == song.ID {
			p.Songs = append(p.Songs[:i], p.Songs[i+1:]...)
			return
		}
	}
}
