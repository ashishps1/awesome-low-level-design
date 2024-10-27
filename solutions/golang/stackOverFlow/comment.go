package stackoverflow

import "time"

type Comment struct {
	ID           int
	Content      string
	Author       *User
	CreationDate time.Time
}

func NewComment(author *User, content string) *Comment {
	return &Comment{
		ID:           generateID(),
		Author:       author,
		Content:      content,
		CreationDate: time.Now(),
	}
}
