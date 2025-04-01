package socialnetworkingservice

import (
	"sync"
	"time"
)

type Post struct {
	ID        string
	UserID    string
	Content   string
	ImageURLs []string
	VideoURLs []string
	Timestamp time.Time
	likes     map[string]bool
	comments  []*Comment
	mu        sync.RWMutex
}

func NewPost(id, userID, content string, imageURLs, videoURLs []string) *Post {
	return &Post{
		ID:        id,
		UserID:    userID,
		Content:   content,
		ImageURLs: imageURLs,
		VideoURLs: videoURLs,
		Timestamp: time.Now(),
		likes:     make(map[string]bool),
		comments:  make([]*Comment, 0),
	}
}

func (p *Post) AddLike(userID string) bool {
	p.mu.Lock()
	defer p.mu.Unlock()
	if !p.likes[userID] {
		p.likes[userID] = true
		return true
	}
	return false
}

func (p *Post) AddComment(comment *Comment) {
	p.mu.Lock()
	defer p.mu.Unlock()
	p.comments = append(p.comments, comment)
}

func (p *Post) GetLikes() []string {
	p.mu.RLock()
	defer p.mu.RUnlock()
	likes := make([]string, 0, len(p.likes))
	for userID := range p.likes {
		likes = append(likes, userID)
	}
	return likes
}

func (p *Post) GetComments() []*Comment {
	p.mu.RLock()
	defer p.mu.RUnlock()
	comments := make([]*Comment, len(p.comments))
	copy(comments, p.comments)
	return comments
}
