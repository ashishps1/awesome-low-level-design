package socialnetworkingservice

import (
	"time"
)

type Notification struct {
	ID        string
	UserID    string
	Type      NotificationType
	Content   string
	Timestamp time.Time
}
