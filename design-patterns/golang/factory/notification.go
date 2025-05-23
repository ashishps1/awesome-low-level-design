package factory

// Notification defines the interface for all notification types
type Notification interface {
	Send(message string)
}
