package socialnetworkingservice

import "time"

type Comment struct {
	ID        string
	UserID    string
	PostID    string
	Content   string
	Timestamp time.Time
}

func NewComment(id, userID, postID, content string) *Comment {
	return &Comment{
		ID:        id,
		UserID:    userID,
		PostID:    postID,
		Content:   content,
		Timestamp: time.Now(),
	}
}
