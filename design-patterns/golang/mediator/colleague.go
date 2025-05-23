package mediator

// Colleague defines the interface for participants in the communication
type Colleague interface {
	SetMediator(mediator Mediator)
	GetName() string
	ReceiveMessage(message string)
}
