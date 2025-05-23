package mediator

// Mediator defines the interface for communication between colleagues
type Mediator interface {
	SendMessage(message string, colleague Colleague)
}
