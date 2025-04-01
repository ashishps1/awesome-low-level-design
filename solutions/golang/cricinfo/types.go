package cricinfo

type MatchStatus int

const (
	MatchStatusScheduled MatchStatus = iota
	MatchStatusInProgress
	MatchStatusCompleted
	MatchStatusAbandoned
)

func (s MatchStatus) String() string {
	return [...]string{"SCHEDULED", "IN_PROGRESS", "COMPLETED", "ABANDONED"}[s]
}
