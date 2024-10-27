package socialnetworkingservice

import (
	"time"
)

type Post struct {
	ID        string
	UserID    string
	Content   string
	ImageUrls []string
	VideoUrls []string
	Timestamp time.Time
	Likes     []string
	Comments  []Comment
}

func NewPost(id, userId, content string, imageUrls, videoUrls, likes []string, comments []Comment) *Post {
	return &Post{
		ID:        id,
		UserID:    userId,
		Content:   content,
		ImageUrls: imageUrls,
		VideoUrls: videoUrls,
		Timestamp: time.Now(),
		Likes:     likes,
		Comments:  comments,
	}
}
