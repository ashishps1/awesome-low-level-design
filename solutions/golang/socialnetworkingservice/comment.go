package socialnetworkingservice

import (
	"time"
)

type Comment struct {
	ID        string
	UserID    string
	PostID    string
	Content   string
	Timestamp time.Time
}

func NewComment(id, userId, postId, content string) *Comment {
	return &Comment{
		ID:        id,
		UserID:    userId,
		PostID:    postId,
		Content:   content,
		Timestamp: time.Now(),
	}
}
