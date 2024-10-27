package cricinfo

type CricinfoSystem struct {
	matchService     *MatchService
	scorecardService *ScorecardService
}

func NewCricinfoSystem() *CricinfoSystem {
	return &CricinfoSystem{
		matchService:     GetMatchService(),
		scorecardService: GetScorecardService(),
	}
}

func (cs *CricinfoSystem) AddMatch(match *Match) {
	cs.matchService.AddMatch(match)
}

func (cs *CricinfoSystem) GetMatch(matchID string) *Match {
	return cs.matchService.GetMatch(matchID)
}

func (cs *CricinfoSystem) GetAllMatches() []*Match {
	return cs.matchService.GetAllMatches()
}

func (cs *CricinfoSystem) UpdateMatchStatus(matchID string, status MatchStatus) {
	cs.matchService.UpdateMatchStatus(matchID, status)
}

func (cs *CricinfoSystem) CreateScorecard(match *Match) string {
	return cs.scorecardService.CreateScorecard(match)
}

func (cs *CricinfoSystem) GetScorecard(scorecardID string) *Scorecard {
	return cs.scorecardService.GetScorecard(scorecardID)
}

func (cs *CricinfoSystem) UpdateScore(scorecardID string, teamID string, score int) {
	cs.scorecardService.UpdateScore(scorecardID, teamID, score)
}

func (cs *CricinfoSystem) AddInnings(scorecardID string, innings *Innings) {
	cs.scorecardService.AddInnings(scorecardID, innings)
}
