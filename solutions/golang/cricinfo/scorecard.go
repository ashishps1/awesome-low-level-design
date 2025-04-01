package cricinfo

import "sync"

type Scorecard struct {
	ID         string
	Match      *Match
	TeamScores map[string]int
	Innings    []*Innings
	mu         sync.RWMutex
}

func NewScorecard(id string, match *Match) *Scorecard {
	return &Scorecard{
		ID:         id,
		Match:      match,
		TeamScores: make(map[string]int),
		Innings:    make([]*Innings, 0),
	}
}

func (s *Scorecard) UpdateScore(teamID string, score int) {
	s.mu.Lock()
	defer s.mu.Unlock()
	s.TeamScores[teamID] = score
}

func (s *Scorecard) AddInnings(innings *Innings) {
	s.mu.Lock()
	defer s.mu.Unlock()
	s.Innings = append(s.Innings, innings)
}
