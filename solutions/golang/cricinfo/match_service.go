package cricinfo

import (
	"sync"
)

type MatchService struct {
	matches map[string]*Match
	mu      sync.RWMutex
}

var (
	matchServiceInstance *MatchService
	matchServiceOnce     sync.Once
)

func GetMatchService() *MatchService {
	matchServiceOnce.Do(func() {
		matchServiceInstance = &MatchService{
			matches: make(map[string]*Match),
		}
	})
	return matchServiceInstance
}

func (ms *MatchService) AddMatch(match *Match) {
	ms.mu.Lock()
	defer ms.mu.Unlock()
	ms.matches[match.ID] = match
}

func (ms *MatchService) GetMatch(matchID string) *Match {
	ms.mu.RLock()
	defer ms.mu.RUnlock()
	return ms.matches[matchID]
}

func (ms *MatchService) GetAllMatches() []*Match {
	ms.mu.RLock()
	defer ms.mu.RUnlock()

	matches := make([]*Match, 0, len(ms.matches))
	for _, match := range ms.matches {
		matches = append(matches, match)
	}
	return matches
}

func (ms *MatchService) UpdateMatchStatus(matchID string, status MatchStatus) {
	ms.mu.Lock()
	defer ms.mu.Unlock()
	if match, exists := ms.matches[matchID]; exists {
		match.Status = status
	}
}
