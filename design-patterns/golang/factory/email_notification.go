package factory

import "fmt"

// EmailNotification represents an email notification
type EmailNotification struct{}

// NewEmailNotification creates a new EmailNotification instance
func NewEmailNotification() *EmailNotification {
	return &EmailNotification{}
}

// Send sends an email notification
func (e *EmailNotification) Send(message string) {
	fmt.Printf("Sending email: %s\n", message)
}
