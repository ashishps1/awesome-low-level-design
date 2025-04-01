package linkedin

import "time"

type Notification struct {
	ID        string
	User      *User
	Type      NotificationType
	Content   string
	Timestamp time.Time
}

func NewNotification(id string, user *User, notifType NotificationType, content string) *Notification {
	return &Notification{
		ID:        id,
		User:      user,
		Type:      notifType,
		Content:   content,
		Timestamp: time.Now(),
	}
}
