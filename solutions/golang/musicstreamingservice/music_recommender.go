package musicstreamingservice

import (
	"sync"
)

type MusicRecommender struct {
	userRecommendations map[string][]*Song
	mu                  sync.RWMutex
}

var (
	recommenderInstance *MusicRecommender
	recommenderOnce     sync.Once
)

func GetMusicRecommender() *MusicRecommender {
	recommenderOnce.Do(func() {
		recommenderInstance = &MusicRecommender{
			userRecommendations: make(map[string][]*Song),
		}
	})
	return recommenderInstance
}

func (mr *MusicRecommender) RecommendSongs(user *User) []*Song {
	mr.mu.RLock()
	defer mr.mu.RUnlock()

	if recommendations, exists := mr.userRecommendations[user.ID]; exists {
		return recommendations
	}
	return make([]*Song, 0)
}
