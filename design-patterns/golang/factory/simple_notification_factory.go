package factory

// SimpleNotificationFactory creates different types of notifications
type SimpleNotificationFactory struct{}

// NewSimpleNotificationFactory creates a new SimpleNotificationFactory instance
func NewSimpleNotificationFactory() *SimpleNotificationFactory {
	return &SimpleNotificationFactory{}
}

// CreateNotification creates a notification based on the type
func (f *SimpleNotificationFactory) CreateNotification(notificationType string) (Notification, error) {
	switch notificationType {
	case "EMAIL":
		return NewEmailNotification(), nil
	case "SMS":
		return NewSMSNotification(), nil
	case "PUSH":
		return NewPushNotification(), nil
	default:
		return nil, fmt.Errorf("unknown notification type: %s", notificationType)
	}
} 