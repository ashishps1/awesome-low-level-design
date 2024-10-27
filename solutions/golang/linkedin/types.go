package linkedin

type NotificationType int

const (
	NotificationTypeConnectionRequest NotificationType = iota
	NotificationTypeMessage
	NotificationTypeJobPosting
)