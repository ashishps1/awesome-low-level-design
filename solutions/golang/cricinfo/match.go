package cricinfo

import "time"

type Match struct {
	ID        string
	Title     string
	Venue     string
	StartTime time.Time
	Teams     []*Team
	Status    MatchStatus
	Scorecard *Scorecard
}

func NewMatch(id, title, venue string, startTime time.Time, teams []*Team) *Match {
	return &Match{
		ID:        id,
		Title:     title,
		Venue:     venue,
		StartTime: startTime,
		Teams:     teams,
		Status:    MatchStatusScheduled,
	}
}
