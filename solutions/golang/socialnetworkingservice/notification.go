package socialnetworkingservice

import "time"

type Notification struct {
	ID        string
	UserID    string
	Type      NotificationType
	Content   string
	Timestamp time.Time
}

func NewNotification(id, userID string, notifType NotificationType, content string) *Notification {
	return &Notification{
		ID:        id,
		UserID:    userID,
		Type:      notifType,
		Content:   content,
		Timestamp: time.Now(),
	}
}
