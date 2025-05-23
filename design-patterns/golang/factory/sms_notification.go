package factory

import "fmt"

// SMSNotification represents an SMS notification
type SMSNotification struct{}

// NewSMSNotification creates a new SMSNotification instance
func NewSMSNotification() *SMSNotification {
	return &SMSNotification{}
}

// Send sends an SMS notification
func (s *SMSNotification) Send(message string) {
	fmt.Printf("Sending SMS: %s\n", message)
}
