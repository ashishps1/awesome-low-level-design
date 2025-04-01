package pubsubsystem

type Subscriber interface {
	OnMessage(message *Message)
}
