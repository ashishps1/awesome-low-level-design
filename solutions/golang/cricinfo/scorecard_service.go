package cricinfo

import (
	"fmt"
	"sync"
	"sync/atomic"
)

type ScorecardService struct {
	scorecards       map[string]*Scorecard
	scorecardCounter int64
	mu               sync.RWMutex
}

var (
	scorecardServiceInstance *ScorecardService
	scorecardServiceOnce     sync.Once
)

func GetScorecardService() *ScorecardService {
	scorecardServiceOnce.Do(func() {
		scorecardServiceInstance = &ScorecardService{
			scorecards: make(map[string]*Scorecard),
		}
	})
	return scorecardServiceInstance
}

func (ss *ScorecardService) CreateScorecard(match *Match) string {
	ss.mu.Lock()
	defer ss.mu.Unlock()

	scorecardID := ss.generateScorecardID(match.ID)
	scorecard := NewScorecard(scorecardID, match)
	ss.scorecards[scorecardID] = scorecard
	return scorecardID
}

func (ss *ScorecardService) GetScorecard(scorecardID string) *Scorecard {
	ss.mu.RLock()
	defer ss.mu.RUnlock()
	return ss.scorecards[scorecardID]
}

func (ss *ScorecardService) UpdateScore(scorecardID string, teamID string, score int) {
	ss.mu.RLock()
	scorecard := ss.scorecards[scorecardID]
	ss.mu.RUnlock()

	if scorecard != nil {
		scorecard.UpdateScore(teamID, score)
	}
}

func (ss *ScorecardService) AddInnings(scorecardID string, innings *Innings) {
	ss.mu.RLock()
	scorecard := ss.scorecards[scorecardID]
	ss.mu.RUnlock()

	if scorecard != nil {
		scorecard.AddInnings(innings)
	}
}

func (ss *ScorecardService) generateScorecardID(matchID string) string {
	counter := atomic.AddInt64(&ss.scorecardCounter, 1)
	return fmt.Sprintf("SC-%s-%04d", matchID, counter)
}
