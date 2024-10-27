package cricinfo

type Innings struct {
	ID            string
	BattingTeamID string
	BowlingTeamID string
	Overs         []*Over
}

func NewInnings(id, battingTeamID, bowlingTeamID string) *Innings {
	return &Innings{
		ID:            id,
		BattingTeamID: battingTeamID,
		BowlingTeamID: bowlingTeamID,
		Overs:         make([]*Over, 0),
	}
}

func (i *Innings) AddOver(over *Over) {
	i.Overs = append(i.Overs, over)
}
