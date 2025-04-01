package musicstreamingservice

import "sync"

type MusicPlayer struct {
	CurrentSong *Song
	IsPlaying   bool
	CurrentTime int
	mu          sync.Mutex
}

func NewMusicPlayer() *MusicPlayer {
	return &MusicPlayer{}
}

func (p *MusicPlayer) PlaySong(song *Song) {
	p.mu.Lock()
	defer p.mu.Unlock()
	p.CurrentSong = song
	p.IsPlaying = true
	p.CurrentTime = 0
	// Implement actual playback logic here
}

func (p *MusicPlayer) PauseSong() {
	p.mu.Lock()
	defer p.mu.Unlock()
	p.IsPlaying = false
	// Implement actual pause logic here
}

func (p *MusicPlayer) SeekTo(time int) {
	p.mu.Lock()
	defer p.mu.Unlock()
	p.CurrentTime = time
	// Implement actual seek logic here
}
